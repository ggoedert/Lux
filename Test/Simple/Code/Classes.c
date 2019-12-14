#include "LuxEngine.h"

#include "Classes.h"

//Base.c
void Base_Constructor(Base *this, virtual_table(Base) *vtable, char *name) {
    this->vtable = vtable;
    this->name = name;    
}
void Base_OtherPrint(Base *this) {
    Debug_Log("Base_OtherPrint - %s", this->name);
}

//DerivedA.c
virtual_table(Base) virtual_table_instance(DerivedA) = {
    DerivedA_Print,
    Base_OtherPrint
};
void DerivedA_Constructor(DerivedA *this, char *name, char *otherName) {
    Base_Constructor(&this->Base, &virtual_table_instance(DerivedA), name);
    this->otherName = otherName;
}
void DerivedA_Print(Base *this) {
    Debug_Log("DerivedA_Print - %s - %s", this->name, ((DerivedA *)this)->otherName);
}

//DerivedB.c
virtual_table(Base) virtual_table_instance(DerivedB) = {
    DerivedB_Print,
    DerivedB_OtherPrint
};
void DerivedB_Constructor(DerivedB *this, char *name, int number) {
    Base_Constructor(&this->Base, &virtual_table_instance(DerivedB), name);
    this->number = number;
}
DerivedB *DerivedB_New(char *name, int number) {
    DerivedB *this = (DerivedB *)malloc(sizeof(DerivedB));
    if (this)
        DerivedB_Constructor(this, name, number);
    return this;
}
void DerivedB_Print(Base *this) {
    Debug_Log("DerivedB_Print - %s - %d", this->name, ((DerivedB *)this)->number);
}
void DerivedB_OtherPrint(Base *this) {
    Debug_Log("DerivedB_OtherPrint");
}

//Classes.c
void DoClassesTest() {
    DerivedA aa;
    Base *bb_ptr;
    
    Debug_Log("* Start Classes Test *");

    DerivedA_Constructor(&aa, "some guy", "other guy");
    bb_ptr = (Base *)DerivedB_New("Marvin", 42);
    aa.Base.vtable->Print((Base *)&aa);
    aa.Base.vtable->OtherPrint((Base *)&aa);
    bb_ptr->vtable->Print(bb_ptr);
    bb_ptr->vtable->OtherPrint(bb_ptr);
    DerivedB_Destructor(&aa);
    DerivedB_Delete(bb_ptr);

    Debug_Log("* End Classes Test *");
}
