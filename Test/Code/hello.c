#include <stdio.h>
#include <stdlib.h>

#include <lEngine.h>

#define class(c) typedef struct c c; struct c
#define virtual_class(c, ...) typedef struct c##_vtable c##_vtable; typedef struct c c; struct c { const c##_vtable* vtable; __VA_ARGS__ }
#define virtual_table(c) const struct c##_vtable
#define virtual_table_instance(c) g_##c##_vtable
#define derived_class(c, b, ...) typedef struct c c; struct c { b b; __VA_ARGS__ }

//Base.h
virtual_class(Base, 
    char* m_name;
);
virtual_table(Base) {
    void (*Print)(Base* this);
    void (*OtherPrint)(Base* this);
};
void BaseConstructor(Base* this, virtual_table(Base)* vtable, char* name);
void BaseOtherPrint(Base* this);
//Base.c
void BaseConstructor(Base* this, virtual_table(Base)* vtable, char* name) {
    this->vtable = vtable;
    this->m_name = name;    
}
void BaseOtherPrint(Base* this) {
    LuxEcho("BaseOtherPrint - %s\n", this->m_name);
}

//DerivedA.h
derived_class(DerivedA, Base,
    char* m_otherName;
);
typedef struct DerivedAX DerivedAX; struct DerivedAX { Base Base; char* m_otherName; };
void DerivedAConstructor(DerivedA* this, char* name, char* otherName);
void DerivedAPrint(Base* this);
//DerivedA.c
virtual_table(Base) virtual_table_instance(DerivedA) = {
    DerivedAPrint,
    BaseOtherPrint
};
void DerivedAConstructor(DerivedA* this, char* name, char* otherName) {
    BaseConstructor(&this->Base, &virtual_table_instance(DerivedA), name);
    this->m_otherName = otherName;
}
void DerivedAPrint(Base* this) {
    LuxEcho("%s - %s\n", this->m_name, ((DerivedA*)this)->m_otherName);
}

//DerivedB.h
derived_class(DerivedB, Base,
    int m_number;
);
void DerivedBConstructor(DerivedB* this, char* name, int number);
void DerivedBPrint(Base* this);
void DerivedBOtherPrint(Base* this);
//DerivedB.c
virtual_table(Base) virtual_table_instance(DerivedB) = {
    DerivedBPrint,
    DerivedBOtherPrint
};
void DerivedBConstructor(DerivedB* this, char* name, int number) {
    BaseConstructor(&this->Base, &virtual_table_instance(DerivedB), name);
    this->m_number = number;
}
void DerivedBPrint(Base* this) {
    LuxEcho("%s - %d\n", this->m_name, ((DerivedB*)this)->m_number);
}
void DerivedBOtherPrint(Base* this) {
    LuxEcho("DerivedBOtherPrint\n");
}

//main.c
void main() {
    DerivedA aa;
    Base* bb_ptr;

    LuxClrScr();
	LuxEcho("%u bytes free.\n", _heapmemavail());

    LuxEcho("Hello, world!\n");
    
    LuxEcho("\n");
	DerivedAConstructor(&aa, "some guy", "other guy");
    bb_ptr = (Base*)malloc(sizeof(DerivedB));
    DerivedBConstructor((DerivedB*)bb_ptr, "Marvin", 42);
    aa.Base.vtable->Print((Base*)&aa);
    aa.Base.vtable->OtherPrint((Base*)&aa);
    bb_ptr->vtable->Print(bb_ptr);
    bb_ptr->vtable->OtherPrint(bb_ptr);
    free(bb_ptr);
	
    while(1);
}
