#include "associations.hpp"
#include "A.hpp"
#include "B.hpp"
#include "Top.hpp"
namespace Model {
template<>
void Top::link<typename TopAComposite::a>(A* object) {
	TopAComposite_a.addAssoc(object);
}
template<>
void Top::unlink<typename TopAComposite::a>(A* object) {
	TopAComposite_a.removeAssoc(object);
}
template<>
void Top::link<typename TopBComposite::b>(B* object) {
	TopBComposite_b.addAssoc(object);
}
template<>
void Top::unlink<typename TopBComposite::b>(B* object) {
	TopBComposite_b.removeAssoc(object);
}

}

