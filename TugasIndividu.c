#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100
#define MAX_PRODUCTS 100
#define MAX_SALES 100
#define MAX_PRODUCT_NAME_LENGTH 25

typedef struct
{
    char username[50];
    char password[50];
} User;

typedef struct
{
    char productName[MAX_PRODUCT_NAME_LENGTH + 1];
    double price;
    int stock;
} Product;

typedef struct
{
    char saleName[MAX_PRODUCT_NAME_LENGTH + 1];
    double totalPrice;
} Sale;

User users[MAX_USERS];
int userCount = 0;

Product products[MAX_PRODUCTS];
int productCount = 0;

Sale sales[MAX_SALES];
int saleCount = 0;

// Deklarasi Fungsi
void mainMenu();
void salesDashboard();
void viewProducts();
void addProduct();
void editProduct();
void deleteProduct();
void viewSales();
void handleTransaction();
void login();
void registerUser();
void saveUsers();
void loadUsers();
void saveProducts();
void loadProducts();
void saveSales();
void loadSales();
void printDivider();
void printProductTable();
void recordSale(char *productName, double totalPrice);

int main()
{
    loadUsers();
    loadProducts();
    loadSales();
    mainMenu();
    return 0;
}

void printDivider()
{
    printf("========================================\n");
}

void printProductTable()
{
    if (productCount == 0)
    {
        printf("| %-4s | %-30s | %-10s | %-5s |\n", "No", "Nama Produk", "Harga", "Stok");
        printf("|------|--------------------------------|------------|-------|\n");
        printf("| %-4s | %-30s | %-10s | %-5s |\n", "-", "Belum ada produk yang tersedia", "-", "-");
    }
    else
    {
        printf("| %-4s | %-30s | %-10s | %-5s |\n", "No", "Nama Produk", "Harga", "Stok");
        printf("|------|--------------------------------|------------|-------|\n");
        for (int i = 0; i < productCount; i++)
        {
            printf("| %-4d | %-30s | Rp%-9.1f | %-5d |\n", i + 1, products[i].productName, products[i].price, products[i].stock);
        }
    }
}

void recordSale(char *productName, double totalPrice)
{
    strcpy(sales[saleCount].saleName, productName);
    sales[saleCount].totalPrice = totalPrice;
    saleCount++;

    saveSales();
}

void mainMenu()
{
    int choice;
    printDivider();
    printf("Selamat Datang Di Aplikasi Inventy\n");
    printDivider();
    printf("1. Login\n2. Daftar\n3. Keluar\n");
    printf("Masukkan pilihan Anda: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        login();
        break;
    case 2:
        registerUser();
        break;
    case 3:
        printf("Keluar...\n");
        exit(0);
        break;
    default:
        printf("Pilihan tidak valid\n");
        mainMenu();
    }
}

void login()
{
    char username[50], password[50];
    printf("Masukkan username: ");
    scanf("%s", username);
    printf("Masukkan password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            printf("Login berhasil! Mengarahkan ke dashboard...\n");
            salesDashboard();
            return;
        }
    }
    printf("Kredensial tidak valid\n");
    mainMenu();
}

void registerUser()
{
    char username[50], password[50];
    printDivider();
    printf("Masukkan username baru: ");
    scanf("%s", username);
    printf("Masukkan password baru: ");
    scanf("%s", password);

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;

    saveUsers();

    printf("Registrasi berhasil!\n");
    mainMenu();
}

void salesDashboard()
{
    int choice;
    printDivider();
    printf("Dashboard Penjualan:\n");
    printDivider();
    printf("1. Lihat Produk\n2. Tambahkan Produk\n3. Edit Produk\n4. Hapus Produk\n5. Lihat Penjualan\n6. Lakukan Transaksi\n7. Logout\n");
    printf("Masukkan pilihan Anda: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        viewProducts();
        break;
    case 2:
        addProduct();
        break;
    case 3:
        editProduct();
        break;
    case 4:
        deleteProduct();
        break;
    case 5:
        viewSales();
        break;
    case 6:
        handleTransaction();
        break;
    case 7:
        printf("Logout...\n");
        mainMenu();
        break;
    default:
        printf("Pilihan tidak valid\n");
        salesDashboard();
    }
}

void viewProducts()
{
    printDivider();
    printf("Produk yang Tersedia:\n");
    printProductTable();
    printDivider();
    salesDashboard();
}

void addProduct()
{
    if (productCount >= MAX_PRODUCTS)
    {
        printf("Tidak bisa menambahkan lebih banyak produk, kapasitas penuh.\n");
    }
    else
    {
        char name[50];
        double price;
        int stock;
        printDivider();
        printf("Masukkan nama produk baru (maks. 20 karakter): ");
        scanf("%s", name);

        if (strlen(name) > MAX_PRODUCT_NAME_LENGTH)
        {
            printf("Nama produk tidak boleh melebihi %d karakter!\n", MAX_PRODUCT_NAME_LENGTH);
        }
        else
        {
            printf("Masukkan harga produk: ");
            scanf("%lf", &price);
            printf("Masukkan stok produk: ");
            scanf("%d", &stock);

            strcpy(products[productCount].productName, name);
            products[productCount].price = price;
            products[productCount].stock = stock;
            productCount++;

            saveProducts();

            printf("Produk berhasil ditambahkan!\n");
        }
        printDivider();
    }
    salesDashboard();
}

void editProduct()
{
    if (productCount == 0)
    {
        printf("Tidak ada produk yang tersedia untuk diedit.\n");
    }
    else
    {
        int productIndex;
        printDivider();
        printf("Pilih produk yang ingin diedit:\n");
        printProductTable();
        printf("Masukkan nomor produk yang ingin diedit (1-%d): ", productCount);
        scanf("%d", &productIndex);

        if (productIndex < 1 || productIndex > productCount)
        {
            printf("Pilihan produk tidak valid\n");
        }
        else
        {
            double newPrice;
            int newStock;
            printf("Masukkan harga baru: ");
            scanf("%lf", &newPrice);
            printf("Masukkan stok baru: ");
            scanf("%d", &newStock);

            products[productIndex - 1].price = newPrice;
            products[productIndex - 1].stock = newStock;

            saveProducts();
            printf("Produk berhasil diedit!\n");
        }
    }
    printDivider();
    salesDashboard();
}

void deleteProduct()
{
    if (productCount == 0)
    {
        printf("Tidak ada produk yang tersedia untuk dihapus.\n");
    }
    else
    {
        int productIndex;
        printDivider();
        printf("Pilih produk yang ingin dihapus:\n");
        printProductTable();
        printf("Masukkan nomor produk yang ingin dihapus (1-%d): ", productCount);
        scanf("%d", &productIndex);

        if (productIndex < 1 || productIndex > productCount)
        {
            printf("Pilihan produk tidak valid\n");
        }
        else
        {
            for (int i = productIndex - 1; i < productCount - 1; i++)
            {
                products[i] = products[i + 1];
            }
            productCount--;
            saveProducts();
            printf("Produk berhasil dihapus!\n");
        }
    }
    printDivider();
    salesDashboard();
}

void viewSales()
{
    printDivider();
    if (saleCount == 0)
    {
        printf("Tidak ada penjualan yang tersedia.\n");
    }
    else
    {
        printf("Daftar Penjualan:\n");
        for (int i = 0; i < saleCount; i++)
        {
            printf("%d. %s - Total: Rp%.1f\n", i + 1, sales[i].saleName, sales[i].totalPrice);
        }
    }
    printDivider();
    salesDashboard();
}

void handleTransaction()
{
    int productIndex;
    int quantity;

    printDivider();
    printf("Pilih produk yang ingin dibeli:\n");
    printProductTable();
    printDivider();
    printf("Masukkan nomor produk yang ingin dibeli: ");
    scanf("%d", &productIndex);
    printf("Masukkan jumlah pembelian: ");
    scanf("%d", &quantity);

    if (productIndex < 1 || productIndex > productCount || quantity > products[productIndex - 1].stock)
    {
        printf("Pilihan produk tidak valid atau stok tidak mencukupi.\n");
    }
    else
    {
        double totalPrice = products[productIndex - 1].price * quantity;
        products[productIndex - 1].stock -= quantity;
        printf("Anda berhasil membeli %d unit %s dengan total harga Rp%.1f\n", quantity, products[productIndex - 1].productName, totalPrice);
        recordSale(products[productIndex - 1].productName, totalPrice);
        saveProducts();
    }

    printDivider();
    salesDashboard();
}

void saveUsers()
{
    FILE *file = fopen("users.dat", "wb");
    fwrite(&userCount, sizeof(int), 1, file);
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
}

void loadUsers()
{
    FILE *file = fopen("users.dat", "rb");
    if (file != NULL)
    {
        fread(&userCount, sizeof(int), 1, file);
        fread(users, sizeof(User), userCount, file);
        fclose(file);
    }
}

void saveProducts()
{
    FILE *file = fopen("products.dat", "wb");
    fwrite(&productCount, sizeof(int), 1, file);
    fwrite(products, sizeof(Product), productCount, file);
    fclose(file);
}

void loadProducts()
{
    FILE *file = fopen("products.dat", "rb");
    if (file != NULL)
    {
        fread(&productCount, sizeof(int), 1, file);
        fread(products, sizeof(Product), productCount, file);
        fclose(file);
    }
}

void saveSales()
{
    FILE *file = fopen("sales.dat", "wb");
    fwrite(&saleCount, sizeof(int), 1, file);
    fwrite(sales, sizeof(Sale), saleCount, file);
    fclose(file);
}

void loadSales()
{
    FILE *file = fopen("sales.dat", "rb");
    if (file != NULL)
    {
        fread(&saleCount, sizeof(int), 1, file);
        fread(sales, sizeof(Sale), saleCount, file);
        fclose(file);
    }
}
