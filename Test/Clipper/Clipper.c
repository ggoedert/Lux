#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <tgi.h>

#include "LuxCollections.h"

#define bitset(v, b)   ((v) |=  (b))
#define bitclear(v, b) ((v) &= ~(b))
#define bitflip(v, b)  ((v) ^=  (b))
#define bitcheck(v, b) ((v) &   (b))

#define INTERSECT 0x1 // if an intersection point
#define ENTRY     0x2 // if an entry point
#define VISITED   0x4 // if the Node has been visited

/****************************************************************************
 *
 * "Clipping" (c) SID, May 6th, 1999
 *
 ***************************************************************************/
/* module Node.h */

class (Node,
    byte x, y, alpha, status;
    Node *next, *prev;
    Node *neighbor; /* the coresponding intersection point */
);

List nodeList;
Node *s, *c, *root;

void Clipper_Init() {
    List_Constructor(&nodeList, sizeof(Node));
}

#ifdef _DEBUG
void Clipper_Finalize() {
    List_Destructor(&nodeList);
}
#endif

void Clipper_Reset() {
    s = nullptr;
    c = nullptr;
    root = nullptr;
    List_Clear(&nodeList);
}

//****************************************************************************
/* module clip.c */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

Node *create(byte x, byte y, byte alpha, byte status, Node *next, Node *prev) {
    Node *new = (Node *) List_VoidAdd(&nodeList);
    new->x = x;
    new->y = y;
    new->alpha = alpha;
    new->status = status;
    new->next = next;
    new->prev = prev;
    if (prev)
        new->prev->next = new;
    if (next)
        new->next->prev = new;
    new->neighbor = nullptr;
    return new;
}

void insert(Node *p, Node *first, Node *last) {
    Node *aux = first;
    while (aux != last && aux->alpha < p->alpha)
        aux = aux->next;
    p->next = aux;
    p->prev = aux->prev;
    p->prev->next = p;
    p->next->prev = p;
}

Node *first(Node *p) {
    Node *aux = p;
    if (aux)
        do aux = aux->next;
        while (aux != p && (!bitcheck(aux->status, INTERSECT) || bitcheck(aux->status, INTERSECT) && bitcheck(aux->status, VISITED)));
    return aux;
}

Node *last(Node *p) {
    Node *aux = p;
    if (aux)
        while (aux->next)
            aux = aux->next;
    return aux;
}

Node *next(Node *p) {
    Node *aux = p;
    while (aux && bitcheck(aux->status, INTERSECT))
        aux = aux->next;
    return aux;
}

void circle(Node *p) {
    Node *aux = last(p);
    aux->prev->next = p;
    p->prev = aux->prev;
    free(aux);
}

byte dist(byte x1, byte y1, byte x2, byte y2) {
    int d = ((int) x1) - ((int) x2);
    if (!d)
        d = ((int) y1) - ((int) y2);
    return d >= 0 ? d : -d;
}

bool I(Node *p1, Node *p2, Node *q1, Node *q2, byte *xint, byte *yint, byte *alpha_p, byte *alpha_q) {
    byte x, y;
    byte p1x = p1->x;
    byte p1y = p1->y;
    byte p2x = p2->x;
    byte p2y = p2->y;
    byte q1x = q1->x;
    byte q1y = q1->y;
    byte q2x = q2->x;
    byte q2y = q2->y;

    if (p1x == p2x) {
        x = p1x;
        y = q1y;
        if (((x < q1x || x > q2x) && (x < q2x || x > q1x)) || ((y < p1y || y > p2y) && (y < p2y || y > p1y)))
            return false;
    }
    else {
        x = q1x;
        y = p1y;
        if (((x < p1x || x > p2x) && (x < p2x || x > p1x)) || ((y < q1y || y > q2y) && (y < q2y || y > q1y)))
            return false;
    }

    *xint = x;
    *yint = y;
    *alpha_p = dist(p1x, p1y, x, y);
    *alpha_q = dist(q1x, q1y, x, y);

    return true;
}

bool test(Node *point, Node *p) {
    Node *aux, *left, i;
    byte type = 0;

    left = create(0, point->y, 0, 0x0, nullptr, nullptr);
    for (aux = p; aux->next; aux = aux->next)
        if (I(left, point, aux, aux->next, &i.x, &i.y, &i.alpha, &i.alpha))
            type++;
    return (bool)(type % 2);
}

void clip() {
    Node *auxs, *auxc, *is, *ic;
    byte xi, yi, alpha_s, alpha_c;
    bool e;

    Node *crt, *new, *old;
    bool forward;

    auxs = last(s);
    create(s->x, s->y, 0, 0x0, nullptr, auxs);
    auxc = last(c);
    create(c->x, c->y, 0, 0x0, nullptr, auxc);

    for (auxs = s; auxs->next; auxs = auxs->next)
        if (!bitcheck(auxs->status, INTERSECT))
            for (auxc = c; auxc->next; auxc = auxc->next)
                if (!bitcheck(auxc->status, INTERSECT))
                    if (I(auxs, next(auxs->next), auxc, next(auxc->next), &xi, &yi, &alpha_s, &alpha_c)) {
                        is = create(xi, yi, alpha_s, INTERSECT, nullptr, nullptr);
                        ic = create(xi, yi, alpha_c, INTERSECT, nullptr, nullptr);
                        is->neighbor = ic;
                        ic->neighbor = is;
                        insert(is, auxs, next(auxs->next));
                        insert(ic, auxc, next(auxc->next));
                    }

    e = !test(s, c);
    for (auxs = s; auxs->next; auxs = auxs->next)
        if (bitcheck(auxs->status, INTERSECT)) {
            if (e)
                bitset(auxs->status, ENTRY);
            else
                bitclear(auxs->status, ENTRY);
            e = !e;
        }

    e = test(c, s);
    for (auxc = c; auxc->next; auxc = auxc->next)
        if (bitcheck(auxc->status, INTERSECT)) {
            if (e)
                bitset(auxc->status, ENTRY);
            else
                bitclear(auxc->status, ENTRY);
            e = !e;
        }

    circle(s);
    circle(c);
    crt = first(s);
    old = nullptr;
    for (; !bitcheck(crt->status, VISITED); crt = crt->neighbor)
        for (forward = bitcheck(crt->status, ENTRY);;) {
            new = create(crt->x, crt->y, 0, 0x0, old, nullptr);
            old = new;
            bitset(crt->status, VISITED);
            crt = forward ? crt->next : crt->prev;
            if (bitcheck(crt->status, INTERSECT)) {
                bitset(crt->status, VISITED);
                break;
            }
        }
    root = old;
}

void add(byte x, byte y, bool source) {
    Node *new;

    new = create(x, y, 0, 0x0, nullptr, nullptr);
    if (source) {
        new->next = s;
        if (s)
            s->prev = new;
        s = new;
    }
    else {
        new->next = c;
        if (c)
            c->prev = new;
        c = new;
    }
}

void quit() {
#ifdef _DEBUG
    Clipper_Finalize();
#endif
    while (true);
}

void redisplay() {
    Node *aux, *poly;
    tgi_clear();

    tgi_setcolor(TGI_COLOR_WHITE);
    poly = s;
    while (true) {
        for (aux = poly; aux->next && aux->next != poly; aux = aux->next)
            tgi_line(aux->x, aux->y, aux->next->x, aux->next->y);
        tgi_line(aux->x, aux->y, poly->x, poly->y);
        if (poly == c)
            break;
        poly = c;
    }

    tgi_setcolor(TGI_COLOR_BLACK);
    for (aux = root; aux->next; aux = aux->next)
        tgi_line(aux->x, aux->y, aux->next->x, aux->next->y);
    tgi_line(aux->x, aux->y, root->x, root->y);
}

void view_node(Node *p) {
    printf("%c%c%c (%03d,%03d) %03d N:%c\n",
        bitcheck(p->status, INTERSECT) ? 'I' : ' ',
        bitcheck(p->status, ENTRY) ? 'E' : ' ',
        bitcheck(p->status, VISITED) ? 'X' : ' ',
        p->x, p->y, p->alpha, p->neighbor ? 'Y' : 'N');
}

void view(Node *p) {
    Node *aux = p;
    puts("");

    if (aux)
        do {
            view_node(aux);
            aux = aux->next;
        } while (aux && aux != p);
}

void calc_result() {
    //go thoght s find intersection that is not entry set in current
    //tag first as current
    //tag state as solid
    //count <- 1
    //keep going to next
    //  if (state is solid) and (count == 3)
    //    add a square
    //    count <- 1
    //  if current is first
    //    stop
    //  if intersection
    //    count <- 1
    //    current <- neighbor
    //    state = !state

    Node *current = s;
    Node *first = nullptr;
    int count = 0;
    bool solid = true;

    current = s;
    do {
        if (bitcheck(current->status, INTERSECT) && !bitcheck(current->status, ENTRY)) {
            first = current;
            count = 1;
            printf("found first\n");
        }
        current = current->next;
    } while (current && !first); //&& first??
    printf("end found first\n");
    
    //if !current???
    
    do {
        printf("*");
        if (solid && count == 3) {
            //add square
            first = current;
            count = 1;
            printf("found other\n");
            break;
        }
        
        if (bitcheck(current->status, INTERSECT)) {
            count = 1;
            current = current->neighbor;
            solid = !solid;
            printf("jump\n");
            break;
        }
        
        current = current->next;
        if (!current) {
            if (solid) {
                printf("*s\n");
                current = s;
            }
            else {
                printf("*c\n");
                current = c;
            }
            break;
        }
    } while (current !=  first);
    
    printf("end find\n");
}

int main() {
    Clipper_Init();
    clrscr();

    Clipper_Reset();

    add(10, 10, true);
    add(50, 10, true);
    add(50, 50, true);
    add(10, 50, true);

    add(30, 30, false);
    add(250, 30, false);
    add(250, 190, false);
    add(30, 190, false);

    clip();

    /**/
    // Load and initialize the driver
    tgi_load_driver(tgi_stddrv);
    tgi_init();
    tgi_clear();

    // display result
    redisplay();
    cgetc();

    // Unload the driver
    tgi_unload();
    /**/

    view(s);
    view(c);
    view(root);

    calc_result();
    quit();
    return EXIT_SUCCESS;
}
