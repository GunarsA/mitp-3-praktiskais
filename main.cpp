#include "utils.hpp"
#include "Product.h"
#include <map>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;

enum class eAction
{
    AddProduct = 1,
    OutputProducts = 2,
    SellProduct = 3,
    ProductInfo = 4,
    Top3MostSold = 5,
    Top3LeastSold = 6,
    Top3MostProfit = 7,
    Top3LeastProfit = 8,
    Top3MostExpensive = 9,
    Top3LeastExpensive = 10,
    Exit = 11
};

eAction promptAction()
{
    std::pair<eAction, std::string> actions[] = {
        {eAction::AddProduct, "Papildināt produktu ar skaitu"},
        {eAction::OutputProducts, "Izvadīt visus produktus uz ekrāna"},
        {eAction::SellProduct, "Pārdot produktu"},
        {eAction::ProductInfo, "Izvadīt datus par produktu"},
        {eAction::Top3MostSold, "Izdrukāt uz ekrāna Top3 visvairāk iztirgotos produktus"},
        {eAction::Top3LeastSold, "Izdrukāt uz ekrāna Top3 vismazāk iztirgotos produktus"},
        {eAction::Top3MostProfit, "Izdrukāt uz ekrāna Top3 tos produktus par kuriem ir visvairāk nopelnīts"},
        {eAction::Top3LeastProfit, "Izdrukāt uz ekrāna Top3 tos produktus par kuriem ir vismazāk nopelnīts"},
        {eAction::Top3MostExpensive, "Izdrukāt uz ekrāna Top3 visdārgākos produktus"},
        {eAction::Top3LeastExpensive, "Izdrukāt uz ekrāna Top3 vislētākos produktus"},
        {eAction::Exit, "Beigt programmu"}};

    cout << "Izvēlieties darbību:\n";
    for (auto action : actions)
    {
        cout << "\t" << (int)action.first << ". " << action.second << endl;
    }

    eAction result;
    input("Izvēlieties darbību [1-11]: ", (int &)result, [](int x) -> bool
          { return x >= 1 && x <= 11; });
    return result;
}

int main()
{
    cout << "3. PRAKTISKAIS" << endl;

    std::map<std::string, Product> products;
    while (true)
    {
        clearConsole();
        eAction action = promptAction();
        switch (action)
        {
        case eAction::AddProduct:
        {
            std::string productName;
            unsigned int amount;
            inputLine("Ievadiet produkta nosaukumu: ", productName);
            input("Ievadiet skaitu: ",amount);
            int unitsAdding;
            products.emplace(std::pair<std::string,Product>(productName,Product(productName.c_str(),0,amount)));
            Product::writeProducts(products);
            // TODO (O.P.): pabeigt šo ig
            break;
        }
        case eAction::OutputProducts:
        {
            Product::fetchProducts(products);
            for(auto& pair : products){
                Product& prod=pair.second;
                prod.print();
                std::cout<<"\n";
            }
            std::cin.get();
            break;
        }
        case eAction::SellProduct:
        {
            std::string productName;
            input("Ievadiet produkta nosaukumu: ", productName);
            if (products.find(productName) == products.end())
            {
                cout << "Produkts \"" << productName << "\" netika atrasts!\n";
                break;
            }
            products[productName].unitsAvailable--;
            products[productName].unitsSold++;
            break;
        }
        case eAction::ProductInfo:
        {
            std::string productName;
            input("Ievadiet produkta nosaukumu: ", productName);
            // TODO (O.P.)
            break;
        }
        case eAction::Top3MostSold:
        {
            // TODO (O.P.)
            break;
        }
        case eAction::Top3LeastSold:
        {
            std::vector<Product> productVec;
            for (auto p : products)
                productVec.push_back(p.second);

            // sort by units sold in ascending order
            std::sort(productVec.begin(), productVec.end(),
                      [](const Product &a, const Product &b) -> bool
                      {
                          return a.unitsSold > b.unitsSold;
                      });

            cout<<"3 vismazāk iztirgotie produkti\n";
            for (int i = 1; i <= 3; i++)
            {
                cout << "Top " << i << ": ";
                if (i <= productVec.size())
                    cout << productVec[i - 1].name;
                cout<<"\n";
            }
            pauseConsole();
            break;
        }
        case eAction::Top3MostProfit:
        {
            std::vector<Product> productVec;
            for (auto p : products)
                productVec.push_back(p.second);

            // sort by (units sold * price) in descending order
            std::sort(productVec.begin(), productVec.end(),
                      [](const Product &a, const Product &b) -> bool
                      {
                          return (a.unitsSold*a.price) < (b.unitsSold*b.price);
                      });

            cout<<"3 produkti, ar kuriem visvairāk nopelnīts\n";
            for (int i = 1; i <= 3; i++)
            {
                cout << "Top " << i << ": ";
                if (i <= productVec.size())
                    cout << productVec[i - 1].name;
                cout<<"\n";
            }
            pauseConsole();
            break;
        }
        case eAction::Top3LeastProfit:
        {
            // TODO (O.P.)
            break;
        }
        case eAction::Top3MostExpensive:
        {
            // TODO (O.P.)
            break;
        }
        case eAction::Top3LeastExpensive:
        {
            std::vector<Product> productVec;
            for (auto p : products)
                productVec.push_back(p.second);

            // sort by price in ascending order
            std::sort(productVec.begin(), productVec.end(),
                      [](const Product &a, const Product &b) -> bool
                      {
                          return a.price > b.price;
                      });

            cout<<"3 vislētākie produkti\n";
            for (int i = 1; i <= 3; i++)
            {
                cout << "Top " << i << ": ";
                if (i <= productVec.size())
                    cout << productVec[i - 1].name;
                cout<<"\n";
            }
            pauseConsole();
            break;
        }
        case eAction::Exit:
        {
            // TODO (O.P.)
            return 0;
        }
        }
    }
}