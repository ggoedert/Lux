#include "LuxTypes.h"

//Base.h
virtual_class (Base, (
        char *name;
    ), (
        void (*Print)(Base *this);
        void (*OtherPrint)(Base *this);
    )
);
void Base_Constructor(Base *this, virtual_table(Base) *vtable, char *name);

//DerivedA.h
derived_class (DerivedA, Base,
    char *otherName;
);
void DerivedA_Constructor(DerivedA *this, char *name, char *otherName);
#define DerivedA_Destructor(this)
void DerivedA_Print(Base *this);

//DerivedB.h
derived_class (DerivedB, Base,
    int number;
);
void DerivedB_Constructor(DerivedB *this, char *name, int number);
#define DerivedB_Destructor(this)
DerivedB *DerivedB_New(char *name, int number);
#define DerivedB_Delete(this) do { DerivedB_Destructor(this); free(this); } while(false)
void DerivedB_Print(Base *this);
void DerivedB_OtherPrint(Base *this);

//Classes.h
void DoClassesTest(void);
