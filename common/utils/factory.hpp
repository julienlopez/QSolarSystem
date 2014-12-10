#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include "singleton.hpp"
#include "defaultfactoryerrorpolicy.hpp"

#include <map>

BEGIN_NAMESPACE_UTILS

/**
 * \class Factory factory.hpp utils/factory.hpp
 * \brief The Factory class provides a generic factory to create object in a polymorphic setting.
 *
 * The Factory works with an AbstractProcuct, a type define as the common interface for all the classes registered in the factory.
 * As new classes inheriting this interface are implemented, they are to be registered to the factory using the registerProduct() method.
 * An id if type IdentifierType is required for each class being registered in the factory.\n
 * This id can later be used to create a new instance of the desired class, using the create() method with the proper id.
 */
template<	class AbstractProduct,
			class IdentifierType,
            class ProductCreator = AbstractProduct(*)(),
			template<typename, class> class FactoryErrorPolicy = DefaultFactoryErrorPolicy
			>
class Factory : public FactoryErrorPolicy<IdentifierType, AbstractProduct>, public Singleton<Factory<AbstractProduct, IdentifierType, ProductCreator, FactoryErrorPolicy> >
{
public:
    typedef FactoryErrorPolicy<IdentifierType, AbstractProduct> error_policy;

    template<class ... Args>
    AbstractProduct create(typename const_parameter_trait<IdentifierType>::type id, Args... args)
	{
		typename AssocMap::const_iterator i = m_associations.find(id);
        if(i != m_associations.end()) return (i->second)(std::forward<Args>(args)...);
        return error_policy::onUnknownType(id);
	}
	
    bool registerProduct(typename const_parameter_trait<IdentifierType>::type id, ProductCreator creator)
	{
        return m_associations.insert(typename AssocMap::value_type(id, creator)).second;
	}
	
    bool unregisterProduct(typename const_parameter_trait<IdentifierType>::type id)
	{
		return m_associations.erase(id) == 1;
	}
	
private:
    typedef std::map<IdentifierType, ProductCreator> AssocMap;
	AssocMap m_associations;
};

END_NAMESPACE_UTILS

#endif
