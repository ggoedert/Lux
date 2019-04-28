#include <stdio.h>
#include <stdlib.h>

#include <lEngine.h>
#include <lClass.h>

//Base.h
virtual_class(Base, (
        char* m_name;
    ), (
        void (*Print)(Base* this);
        void (*OtherPrint)(Base* this);
    )
);
void Base_Constructor(Base* this, virtual_table(Base)* vtable, char* name);
#define Base_Destructor(this)
void Base_OtherPrint(Base* this);
//Base.c
void Base_Constructor(Base* this, virtual_table(Base)* vtable, char* name) {
    this->vtable = vtable;
    this->m_name = name;    
}
void Base_OtherPrint(Base* this) {
    LuxEcho("Base_OtherPrint - %s\n", this->m_name);
}

//DerivedA.h
derived_class(DerivedA, Base,
    char* m_otherName;
);
void DerivedA_Constructor(DerivedA* this, char* name, char* otherName);
#define DerivedA_Destructor(this)
void DerivedA_Print(Base* this);
//DerivedA.c
virtual_table(Base) virtual_table_instance(DerivedA) = {
    DerivedA_Print,
    Base_OtherPrint
};
void DerivedA_Constructor(DerivedA* this, char* name, char* otherName) {
    Base_Constructor(&this->Base, &virtual_table_instance(DerivedA), name);
    this->m_otherName = otherName;
}
void DerivedA_Print(Base* this) {
    LuxEcho("DerivedA_Print - %s - %s\n", this->m_name, ((DerivedA*)this)->m_otherName);
}

//DerivedB.h
derived_class(DerivedB, Base,
    int m_number;
);
void DerivedB_Constructor(DerivedB* this, char* name, int number);
#define DerivedB_Destructor(this)
DerivedB* DerivedB_New(char* name, int number);
#define DerivedB_Delete(this) do { DerivedB_Destructor(this); free(this); } while(0)
void DerivedB_Print(Base* this);
void DerivedB_OtherPrint(Base* this);
//DerivedB.c
virtual_table(Base) virtual_table_instance(DerivedB) = {
    DerivedB_Print,
    DerivedB_OtherPrint
};
void DerivedB_Constructor(DerivedB* this, char* name, int number) {
    Base_Constructor(&this->Base, &virtual_table_instance(DerivedB), name);
    this->m_number = number;
}
DerivedB* DerivedB_New(char* name, int number) {
    DerivedB* new_ptr = (DerivedB*)malloc(sizeof(DerivedB));
    if (new_ptr)
        DerivedB_Constructor(new_ptr, name, number);
    return new_ptr;
}
void DerivedB_Print(Base* this) {
    LuxEcho("DerivedB_Print - %s - %d\n", this->m_name, ((DerivedB*)this)->m_number);
}
void DerivedB_OtherPrint(Base* this) {
    LuxEcho("DerivedB_OtherPrint\n");
}

//main.c
void main() {
    DerivedA aa;
    Base* bb_ptr;

    LuxClrScr();
	LuxEcho("%u bytes free.\n", _heapmemavail());

    LuxEcho("Hello, world!\n");
    
    LuxEcho("\n");
	DerivedA_Constructor(&aa, "some guy", "other guy");
    bb_ptr = (Base*)DerivedB_New("Marvin", 42);
    aa.Base.vtable->Print((Base*)&aa);
    aa.Base.vtable->OtherPrint((Base*)&aa);
    bb_ptr->vtable->Print(bb_ptr);
    bb_ptr->vtable->OtherPrint(bb_ptr);
    DerivedB_Destructor(&aa);
    DerivedB_Delete(bb_ptr);
	
    while(1);
}
