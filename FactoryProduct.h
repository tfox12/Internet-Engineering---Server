#ifndef _SERVER_FACTORYPRODUCT_
#define _SERVER_FACTORYPRODUCT_

#include <string>

namespace Server
{

    template<typename FACTORY,typename PRODUCT>
    class FactoryProduct
    {
    public:

        virtual std::string id() = 0; 

    private:

    };

    static
    {
        template<typename FACTORY,typename PRODUCT>
        FactoryProduct<FACTORY,PRODUCT>::p = new PRODUCT();

        template<typename FACTORY,typename PRODUCT>
        {

        }
    }

}

#endif