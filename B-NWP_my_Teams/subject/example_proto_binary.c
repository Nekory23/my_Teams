#include <stddef.h>

/**
** enum représentant la fonction à appeler, et donc le type de donnée qui va suivre
*/
enum type {
    HELP,
    LOGIN,
    /*...*/
};


/**
** header qui sera envoyé avec chaque message.
*/
typedef struct header_s {
    unsigned short sz; // nombre d'octet envoyé, a comparer avec le retour de read pour s'assurer qu'on a lu le message complet.
    enum type type;    // type de message. Cela permet d'appeler la bonne fonction, et ça donne des informations sur la nature du message.
} header_t;


// 00 00 00 00 00 00 00 06  // représentation hexadecimale du nombre 6 (big endian + représentation "logique")
// 06 00 00 00 00 00 00 00  // little endian

typedef struct login login_t;
/**
** exemple de fonction à appeler une fois le message récupéré. Toutes les fonctions doivent avoir 
** la même signature afin de les mettres dans un tableau de ptr sur fonction.
*/
void do_login(void *data) {
    login_t *log = (login_t *)data;
    char *username = malloc(log->sz);
    memcopy(username, log->username, log->sz);
}

/**
** Envoie de message générique:
** - Une structure représente la donnee, et une autre permet de définir le header.
** - Pour envoyer:
**   1. on utilise une fonction générique qui prends un type et un void *.
**   2. On alloue suffisemment de mémoire consécutive pour le header et la donnée
**   3. on initialise le header
**   4. on copie la donnée après le header
**   5. on write/send la taille totale, en passant un pointeur sur le début du message
*/

/**
** cette structure représente une payload. En l'occurence il s'agit d'une payload de taille variable, ce qui peut necessiter plus de traitement.
** on aurait aussi pu envoyer une payload de taille fixe, sans envoie de la taille, mais avec un char [sz] ou tout autre type.
*/
typedef struct login {
    size_t sz;
    char username[0];
} login_t;

/**
** type générique pour envoyer les message. il contient un header (les champs du header pourraient être directement dans la structure),
** ainsi qu'un champs data d'une taille de 0, qui donne un pointeur sur le byte qui suit la structure.
*/
typedef struct msg {
    header_t head;
    char data[0];
} msg_t;

void send_msg(enum type t, void *data, size_t sz) {
    msg_t *msg = malloc(sizeof(msg_t) + sz);
    memcpy(msg->data, data, sz);
    msg->head.type = t;
    msg->head.sz = sz + sizeof(msg_t);
    write(1, msg, msg->head.sz);
}

void rcv_msg() {
    char buf[1500];
    msg_t *msg;

    size_t r = read(1, buf, 1500);
    msg = (msg_t *)buf;

    if (msg->head.sz == r) {
        FUN[msg->head.type]((void *)msg->data);
    }
}


/**
** Deuxième méthode. Le header est contenu dans chacune des structures représentant le message
*/
typedef struct {
    header_t head;
    char usename[50];
} login_query_t;


/**
** le l'addresse du premier champs d'une structure est également l'addresse de la structure. on appelle cette fonction en passant l´ addresse de la structure login_query_t directement.
*/
void send(header_t * msg) {
    write(1, msg, msg->sz);
}


void recv() {
    char buf[1500];
    header_t *head;

    size_t r = read(0, buf, 1500);
    head = (header_t *)buf;

    if (head->sz == r) {
        FUN[head->type]((void *)buf);
    }

}
