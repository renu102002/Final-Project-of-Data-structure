#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Asset {
public:
    string getName() const { return name; }
    string getCategory() const { return category; }
    double getValue() const { return value; }
    bool getInStock() const { return inStock; }
    int getQuantity() const { return quantity; }

    void setName(const string& newName) { name = newName; }
    void setCategory(const string& newCategory) { category = newCategory; }
    void setValue(double newValue) { value = newValue; }
    void setInStock(bool newInStock) { inStock = newInStock; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }

private:
    string name;
    string category;
    double value;
    bool inStock;
    int quantity;
};

void addAsset(vector<Asset>& assets) {
    Asset newAsset;
    string input;
    cout << "Enter Asset name: ";
    getline(cin >> ws, input);
    newAsset.setName(input);
    cout << "Enter Asset category: ";
    getline(cin >> ws, input);
    newAsset.setCategory(input);
    cout << "Enter Asset value: $";
    cin >> input;
    newAsset.setValue(stod(input));
    cout << "Enter Quantity: ";
    cin >> input;
    newAsset.setQuantity(stoi(input));
    newAsset.setInStock(true);
    assets.push_back(newAsset);
}

void viewAssets(const vector<Asset>& assets) {
    cout << "Assets:" << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;
    cout << setw(20) << "Name" << setw(20) << "Category" << setw(15) << "Value" << setw(15) << "Quantity" << setw(12) << "In Stock" << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;
    for (const auto& asset : assets) {
        cout << setw(20) << asset.getName() << setw(20) << asset.getCategory() << setw(10) << "$" << asset.getValue() << setw(15) << asset.getQuantity() << setw(12) << (asset.getInStock() ? "Yes" : "No") << endl;
    }
    cout << "------------------------------------------------------------------------------------------------" << endl;
}

void markAssetOutOfStock(vector<Asset>& assets) {
    int index;
    cout << "Enter index of asset to mark as out of stock: ";
    cin >> index;
    if (index >= 0 && index < assets.size()) {
        assets[index].setInStock(false);
        cout << "Asset marked as out of stock." << endl;
    }
    else {
        cout << "Invalid index." << endl;
    }
}

void deleteAsset(vector<Asset>& assets) {
    int index;
    cout << "Enter index of asset to delete: ";
    cin >> index;
    if (index >= 0 && index < assets.size()) {
        assets.erase(assets.begin() + index);
        cout << "Asset was deleted." << endl;
    }
    else {
        cout << "Invalid index." << endl;
    }
}

void saveAssetsToFile(const vector<Asset>& assets, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& asset : assets) {
            outFile << asset.getName() << "," << asset.getCategory() << "," << asset.getValue() << "," << asset.getQuantity() << "," << (asset.getInStock() ? "1" : "0") << endl;
        }
        cout << "Assets saved to " << filename << endl;
    }
    else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

void loadAssetsFromFile(vector<Asset>& assets, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        assets.clear();
        string line;
        while (getline(inFile, line)) {
            Asset asset;
            size_t commaPos = line.find(',');
            asset.setName(line.substr(0, commaPos));
            line.erase(0, commaPos + 1);
            
            commaPos = line.find(',');
            asset.setCategory(line.substr(0, commaPos));
            line.erase(0, commaPos + 1);
            
            commaPos = line.find(',');
            asset.setValue(stod(line.substr(0, commaPos)));
            line.erase(0, commaPos + 1);
            
            commaPos = line.find(',');
            asset.setQuantity(stoi(line.substr(0, commaPos)));
            line.erase(0, commaPos + 1);
            
            asset.setInStock(line == "1");
            
            assets.push_back(asset);
        }
        cout << "Assets loaded from " << filename << endl;
    }
    else {
        cout << "Error: Unable to open file for reading. Creating new file." << endl;
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Error: Unable to create file." << endl;
        }
    }
}

int main() {
    vector<Asset> assets;
    string filename = "assets.txt";
    loadAssetsFromFile(assets, filename);

    int choice;
    do {
        cout << "\nAsset Management System" << endl;
        cout << "1. Add Asset" << endl;
        cout << "2. View Assets" << endl;
        cout << "3. Mark Asset as Out of Stock" << endl;
        cout << "4. Delete Asset" << endl;
        cout << "5. Save Assets" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addAsset(assets);
            break;
        case 2:
            viewAssets(assets);
            break;
        case 3:
            markAssetOutOfStock(assets);
            break;
        case 4:
            deleteAsset(assets);
            break;
        case 5:
            saveAssetsToFile(assets, filename);
            break;
        case 6:
            cout << "Exiting program. Saving assets..." << endl;
            saveAssetsToFile(assets, filename);
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }
    } while (choice != 6);

    return 0;
}
