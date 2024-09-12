#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib> 
using namespace std;

class Product {
public:
    string id;
    string name;
    double price;

    Product() : id(""), name(""), price(0.00) {}

    Product(const string& id, const string& name, double price) 
        : id(id), name(name), price(price) {}

    static string generateProductID(const string& prefix, int number) {
        string id = prefix + to_string(number);
        for (char& c : id) {
            c = toupper(c);
        }
        return id;
    }
};

class ShoppingCart {
public:
    Product items[10];
    int quantities[10];
    int itemCount;

    ShoppingCart() : itemCount(0) {}

    void addProduct(const Product& product, int quantity) {
        if (itemCount < 10) {
            items[itemCount] = product;
            quantities[itemCount] = quantity;
            itemCount++;
        } else {
            cout << "Cart is full, cannot add more products." << endl;
        }
    }

    void viewCart() const {
        if (itemCount == 0) {
            cout << "Shopping cart is empty." << endl;
            return;
        }

        cout << "\nShopping Cart:\n";
        cout << left << setw(12) << "Product ID" << setw(20) << "Name" 
             << setw(10) << "Price" << setw(10) << "Quantity" << endl;

        double totalAmount = 0.0;
        for (int i = 0; i < itemCount; i++) {
            const Product& product = items[i];
            int quantity = quantities[i];
            totalAmount += product.price * quantity;
            cout << left << setw(12) << product.id << setw(20) << product.name 
                 << setw(10) << fixed << setprecision(2) << product.price 
                 << setw(10) << quantity << endl;
        }

        cout << "Total Amount: " << fixed << setprecision(2) << totalAmount << endl;
    }

    bool isEmpty() const {
        return itemCount == 0;
    }

    void clear() {
        itemCount = 0;
    }
};

class Order {
public:
    int orderID;
    Product items[10];
    int quantities[10];
    int itemCount;
    double totalAmount;
    string status;

    Order() : orderID(0), itemCount(0), totalAmount(0.0), status("Pending") {}

    Order(int id) : orderID(id), itemCount(0), totalAmount(0.0), status("Pending") {}

    void addItem(const Product& product, int quantity) {
        if (itemCount < 10) {
            items[itemCount] = product;
            quantities[itemCount] = quantity;
            totalAmount += product.price * quantity;
            itemCount++;
        } else {
            cout << "Order item limit reached." << endl;
        }
    }

    void updateStatus(const string& newStatus) {
        status = newStatus;
    }

    void displayOrder() const {
        cout << "\nOrder ID: " << orderID << endl;
        cout << left << setw(12) << "Product ID" << setw(20) << "Name" 
             << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        for (int i = 0; i < itemCount; i++) {
            const Product& product = items[i];
            int quantity = quantities[i];
            cout << left << setw(12) << product.id << setw(20) << product.name 
                 << setw(10) << fixed << setprecision(2) << product.price 
                 << setw(10) << quantity << endl;
        }
        cout << "Total Amount: " << fixed << setprecision(2) << totalAmount << endl;
        cout << "Order Status: " << status << endl;
    }
};

void viewProducts(Product products[], int productCount) {
    cout << "\nAvailable Products:\n\n";
    cout << left << setw(20) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << endl;
    for (int i = 0; i < productCount; i++) {
        const Product& product = products[i];
        cout << left << setw(20) << product.id << setw(20) << product.name 
             << setw(10) << fixed << setprecision(2) << product.price << endl;
    }
}

void addProductToCart(ShoppingCart& cart, Product products[], int productCount) {
    string productId;
    while (true) {
        cout << "Enter the ID of the product you want to add to the shopping cart: ";
        cin >> productId;
        for (char& c : productId) {
            c = toupper(c);
        }

        bool found = false;
        for (int i = 0; i < productCount; i++) {
            if (products[i].id == productId) {
                int quantity;
                cout << "Enter quantity: ";
                cin >> quantity;
                cart.addProduct(products[i], quantity);
                cout << "Added to cart." << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Invalid Product ID. Please try again." << endl;
        }

        char another;
        cout << "Do you want to add another product? (Y/N): ";
        cin >> another;
        if (tolower(another) != 'y') break; 
    }
}

void checkout(ShoppingCart& cart, Order orders[], int& orderCount, int& orderID) {
    cart.viewCart();
    if (cart.isEmpty()) {
        cout << "Cannot checkout an empty cart." << endl;
        return;
    }

    char checkout;
    cout << "Do you want to check out all the products? (Y/N): ";
    cin >> checkout;

    if (tolower(checkout) == 'y') {
        if (orderCount < 10) {
            Order order(orderID++);
            for (int i = 0; i < cart.itemCount; i++) {
                order.addItem(cart.items[i], cart.quantities[i]);
            }
            order.updateStatus("Completed");
            orders[orderCount++] = order;
            cart.clear(); 
            cout << "Checkout successful!" << endl;
        } else {
            cout << "Order limit reached, cannot place more orders." << endl;
        }
    }
}

void viewOrders(const Order orders[], int orderCount) {
    if (orderCount == 0) {
        cout << "No orders have been placed yet." << endl;
    } else {
        cout << "\nOrders:\n";
        for (int i = 0; i < orderCount; i++) {
            orders[i].displayOrder();
        }
    }
}

int main() {
    Product products[5] = {
        Product(Product::generateProductID("Proid", 1), "Chicken", 200.00),
        Product(Product::generateProductID("Proid", 2), "Milk", 150.00),
        Product(Product::generateProductID("Proid", 3), "Yogurt", 80.00),
        Product(Product::generateProductID("Proid", 4), "Banana", 120.00),
        Product(Product::generateProductID("Proid", 5), "Tuna", 60.00)
    };

    ShoppingCart cart;
    Order orders[10];
    int orderCount = 0;
    int orderID = 1;
    int choice;
    bool running = true; 

    while (running) {
        
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "---------------------------------" << endl;
        cout << "       Online Grocery Store      " << endl;
        cout << "---------------------------------" << endl;
        cout << "\n\nMenu:\n";
        cout << "1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. View Orders\n";
        cout << "4. Exit\n";
        cout << "Select Choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewProducts(products, 5);
                addProductToCart(cart, products, 5);
                break;
            case 2:
                cart.viewCart();
                if (!cart.isEmpty()) {
                    checkout(cart, orders, orderCount, orderID);
                }
                break;
            case 3:
                viewOrders(orders, orderCount);
                break;
            case 4:
                cout << "Exiting the program." << endl;
                running = false; 
                break;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
        }

        
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
