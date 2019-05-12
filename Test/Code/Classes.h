#include <lDefs.h>
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

//DerivedA.h
derived_class(DerivedA, Base,
    char* m_otherName;
);
void DerivedA_Constructor(DerivedA* this, char* name, char* otherName);
#define DerivedA_Destructor(this)
void DerivedA_Print(Base* this);

//DerivedB.h
derived_class(DerivedB, Base,
    int m_number;
);
void DerivedB_Constructor(DerivedB* this, char* name, int number);
#define DerivedB_Destructor(this)
DerivedB* DerivedB_New(char* name, int number);
#define DerivedB_Delete(this) do { DerivedB_Destructor(this); free(this); } while(false)
void DerivedB_Print(Base* this);
void DerivedB_OtherPrint(Base* this);

//Classes.h
void DoClassesTest(void);
