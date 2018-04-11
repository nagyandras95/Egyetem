// Assoc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <map>
#include <list>



template<class FirstClassRole, class SecondClassRole>
class Association : public FirstClassRole, public SecondClassRole {
public:

	Association () {
		FirstClassRole::association = this;
		SecondClassRole::association = this;
	}

	void link (typename FirstClassRole::RoleType* first, FirstClassRole*, typename SecondClassRole::RoleType* second, SecondClassRole*) {
		LeftRoleTable[first].add (second);
		RigthRoleTable[second].add (first);
	}

	void link (typename SecondClassRole::RoleType* first, SecondClassRole*, typename FirstClassRole::RoleType* second, FirstClassRole*) {
		RigthRoleTable[first].add (second);
		LeftRoleTable[second].add (first);
	}

	void unlink (typename FirstClassRole::RoleType* first, FirstClassRole*, typename SecondClassRole::RoleType* second, SecondClassRole*) {
		LeftRoleTable[first].remove (second);
		RigthRoleTable[second].remove (first);
	}

	void unlink (typename SecondClassRole::RoleType* first, SecondClassRole*, typename FirstClassRole::RoleType* second, FirstClassRole*) {
		RigthRoleTable[first].remove (second);
		LeftRoleTable[second].remove (first);
	}

	const typename SecondClassRole::CollectionType& get (typename FirstClassRole::RoleType* left, SecondClassRole*) {
		return LeftRoleTable[left];
	}

	const typename FirstClassRole::CollectionType& get (typename SecondClassRole::RoleType* rigth, FirstClassRole*) {
		return RigthRoleTable[rigth];
	}

private:
	std::map<typename FirstClassRole::RoleType*, typename SecondClassRole::CollectionType> LeftRoleTable;
	std::map<typename SecondClassRole::RoleType*, typename FirstClassRole::CollectionType> RigthRoleTable;

};

template<typename T, int low, int up, typename Container = std::list<T*>>
class Property {
public:
	void add (T* o) {
		objects.push_back (o);
	}

	void remove (T* o) {
		objects.remove (o);
	}

	T* selectAny () {
		return objects.back ();
	}

	typename Container::size_type count () {
		return objects.size ();
	}



private:
	Container objects;
};


template<typename T, int low>
class Property<T, low, 1> {
public:
	void add (T* o) {
		object = o;
	}

	void remove (T* o) {
		assert (o == object);
		if (o == object) {
			object = nullptr;
		}
	}

	T* selectAny () {
		return object;
	}

	int count () {
		return object == nullptr ? 0 : 1;
	}

private:
	T * object = nullptr;
};


template<class FirstClassRole, class SecondClassRole>
class AssocOwner {
public:
	using AssocType = Association<FirstClassRole, SecondClassRole>;

	typename AssocOwner<FirstClassRole, SecondClassRole>::AssocType* association = nullptr;

};

template<typename FirstClassRole, class SecondClassRole, class EndType, int lowMul, int upMul>
struct AssocEnd : public AssocOwner<FirstClassRole, SecondClassRole> {
	typedef Property<typename EndType, lowMul, upMul> CollectionType;
	typedef EndType RoleType;
};

template<typename L, typename LE, typename R, typename RE>
void link (L* lobject, LE* leftRole, R* rightObject, RE* rigthRole) {
	leftRole->association->link (lobject, leftRole, rightObject, rigthRole);
}

template<typename L, typename LE, typename R, typename RE>
void unlink (L* lobject, LE* leftRole, R* rightObject, RE* rigthRole) {
	leftRole->association->unlink (lobject, leftRole, rightObject, rigthRole);
}

class ModelObject {
public:
	/*template<typename Role, typename AssocType>
	const auto& assoc(const AssocType& association) {
		return association.get<Role>(static_cast<typename Role::RoleType*>(this));
	}*/

	template<typename Role>
	const auto& assoc(Role* role) {
		return role->association->get(static_cast<typename Role::RoleType*>(this), role);
	}

};

class A : public ModelObject {
public:
	int id;
};
struct a1End;
struct a2End;

struct a1End : public AssocEnd<a1End, a2End, A, 1, 1> {
	a1End* a1 = this;
};

struct a2End : public AssocEnd<a1End, a2End, A, 1, 1> {
	a2End * a2 = this;
};


int main()
{
	A a1, a2;
	a1.id = 1;
	a2.id = 2;

	Association<a1End, a2End> assocName;

	link (&a1, assocName.a1, &a2, assocName.a2);
	unlink (&a1, assocName.a1, &a2, assocName.a2);
	a2End::CollectionType a2P = a1.assocName(assocName.a2);


    return 0;
}

