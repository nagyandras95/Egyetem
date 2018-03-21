//

#include "stdafx.h"
#include <assert.h>
#include <map>
#include <list>



template<class FirstClassType, class FirstClassRole, class SecondClassType, class SecondClassRole>
class AssociationNN {
public:
	void link (FirstClassType* first, FirstClassRole, SecondClassType* second, SecondClassRole) {
		LeftRoleTable[first].push_back (second);
		RigthRoleTable[second].push_back (first);
	}

	void link (SecondClassType* first, SecondClassRole, FirstClassType* second, FirstClassRole) {
		RigthRoleTable[first].push_back (second);
		LeftRoleTable[second].push_back (first);
	}

	std::list<SecondClassType*> get (FirstClassType* left, FirstClassRole) {
		return LeftRoleTable[left];
	}

	std::list<FirstClassType*> get (SecondClassType* rigth, SecondClassRole) {
		return RigthRoleTable[rigth];
	}

private:
	std::map<typename FirstClassType*, std::list<SecondClassType*>> LeftRoleTable;
	std::map<typename SecondClassType*, std::list<FirstClassType*>> RigthRoleTable;
	
};


template<class FirstClassRoleType, class SecondClassRoleType>
class AssociationNNAlt {
public:
	template<typename FirstType, typename SecondType>
	void link (typename FirstType::RoleType* first, typename SecondType::RoleType* second) {
		assert (false);
	}

	template<>
	void link<typename FirstClassRoleType, SecondClassRoleType> (typename FirstClassRoleType::RoleType* first, typename SecondClassRoleType::RoleType* second) {
		LeftRoleTable[first].push_back (second);
		RigthRoleTable[second].push_back (first);
	}

	template<>
	void link<typename SecondClassRoleType, typename FirstClassRoleType> (typename SecondClassRoleType::RoleType* first, typename FirstClassRoleType::RoleType* second) {
		RigthRoleTable[first].push_back (second);
		LeftRoleTable[second].push_back (first);
	}

	template<typename ParamType>
	auto get (typename ParamType::RoleType* o) {
		assert (false);
	}

	template<>
	auto get<typename FirstClassRoleType> (typename FirstClassRoleType::RoleType* o) {
		return LeftRoleTable[o];
	}

	template<>
	auto get<typename SecondClassRoleType> (typename SecondClassRoleType::RoleType* o) {
		return RigthRoleTable[o];
	}

private:
	std::map<typename FirstClassRoleType::RoleType*, std::list<typename SecondClassRoleType::RoleType*>> LeftRoleTable;
	std::map<typename SecondClassRoleType::RoleType*, std::list<typename FirstClassRoleType::RoleType*>> RigthRoleTable;

};


class A {
public:
	int id;
};


enum class A1 {
	Selector
};

enum class A2 {
	Selector
};

struct a1 {
	typedef A RoleType;
};
struct a2 {
	typedef A RoleType;
};


// uj megoldasok..
struct a1Descriptor;
struct a2Descriptor;

struct a1Descriptor : public AssocRole<a1Descriptor,a2Descriptor>{
	typedef A RoleType;
	a1Descriptor* a1;
	// collection type..
};

struct a2Descriptor : public AssocRole<a1Descriptor,a2Descriptor>{
	typedef A RoleType;
	a2Descriptor* a2;
	// collection type..
};

template<int ID, class R>
struct Role {
	typedef R RoleType;
};

struct a1 {
	typedef A RoleType;
	//collection type..
};

struct a2 {
	typedef A RoleType;
	//collection type..
};
// helyett
using a1 = Role<1,A>; // + collection typot meg at kell gondolni..
using a2 = Role<2,A>;



int main()
{
	AssociationNN<A, A1, A, A2> aAssoc;
	//vs
	AssociationNNAlt<a1, a2 > altAssoc;
	
	Association<a1Descriptor, a2Descriptor> descAssoc;
	//vs
	Association<a1, a2> roleAssoc;

	A a1;
	a1.id = 1;
	A a2;
	a2.id = 2;
	
	// uj megoldasok..
	Action::link(a1, descAssoc.a1, a2, descAssoc.a2);
	a1.assoc(descAssoc.a1);
	a2.assoc(descAssoc.a2);
	//vs
	Action::link(a1, roleAssoc(a1()), a2, roleAssoc(a2));
	a1.assoc(roleAssoc(a1));
	a2.assoc(roleAssoc(a2));
	

	aAssoc.link (&a1, A1::Selector, &a2, A2::Selector);
	altAssoc.link<ARoleStruct::a1, ARoleStruct::a2> (&a1, &a2);

	std::list<A*> rigthObjectsA1 = aAssoc.get (&a1, A1::Selector);
	std::list<A*> leftObjectsA1 = aAssoc.get (&a1, A2::Selector);
	std::list<A*> rigthObjectsA2 = aAssoc.get (&a2, A1::Selector);
	std::list<A*> leftObjectsA2 = aAssoc.get (&a2, A2::Selector);

	
	std::list<A*> rigthObjectsA1alt = altAssoc.get<ARoleStruct::a1> (&a1);
	std::list<A*> leftObjectsA1alt = altAssoc.get<ARoleStruct::a2> (&a1);
	std::list<A*> rigthObjectsA2alt = altAssoc.get<ARoleStruct::a1> (&a2);
	std::list<A*> leftObjectsA2alt = altAssoc.get<ARoleStruct::a2> (&a2);
	


    return 0;
}

