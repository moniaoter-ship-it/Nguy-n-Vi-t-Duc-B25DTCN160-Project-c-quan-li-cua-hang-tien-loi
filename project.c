#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PRODUCTS 100
#define MAX_HISTORY 500

/* ====== CAU TRUC ====== */
typedef struct {
    char productId[16];
    char name[64];
    char unit[16];
    int qty;
    int status; 
} Product;

typedef struct {
    char productId[16];
    int amount;
    int type; // 1: Nhap, 2: Xuat
    char time[32];
} Transaction;

/* ====== BIEN GLOBAL ====== */
Product list[MAX_PRODUCTS];
Transaction history[MAX_HISTORY];
int count = 0;
int historyCount = 0;

/* ====== KHAI BAO HAM ====== */
void clear_input();
int input_int();
int is_empty(const char *s);
void get_time_str(char *buf, int size);
void str_to_lower(char *s);

int find_product_by_id(const char *id);
void print_product_row(int idx);

void init_list_sample();
void add_product();
void update_product();
void manage_status();
void search_products();
void paginate_products();
void sort_products_menu(); // Gi? nguyên tên hàm g?i trong switch-case
void import_product();
void export_product();
void show_history();

/* ========================== MAIN ============================= */

int main() {
    int choice;

    init_list_sample(); 

    while (1) {
        printf("\n==========================================\n");
        printf("|           MENU QUAN LY KHO             |\n");
        printf("|========================================|\n");
        printf("| 1. Them ma hang moi                    |\n");
        printf("| 2. Cap nhat thong tin                  |\n");
        printf("| 3. Quan li trang thai                  |\n");
        printf("| 4. Tra cuu                             |\n");
        printf("| 5. Danh sach (Phan trang)              |\n");
        printf("| 6. Danh sach sap xep                   |\n");
        printf("| 7. Giao dich xuat/nhap khau hang hoa   |\n");
        printf("| 8. Lich su xuat/nhap                   |\n");
        printf("| 0. Thoat                               |\n");
        printf("|========================================|\n");
        printf("Lua chon: ");
        choice = input_int();

        switch (choice) {
            case 1: add_product(); break;
            case 2: update_product(); break;
            case 3: manage_status(); break;
            case 4: search_products(); break;
            case 5: paginate_products(); break;
            case 6: sort_products_menu(); break;
            case 7:
            while (1) {
                printf("\n--- MENU GIAO DICH ---\n");
                printf("1. Nhap hang\n2. Xuat hang\n0. Thoat\nLua chon: ");
                int ch = input_int();
                if (ch == 1) {
                    import_product();
                } else if (ch == 2) {
                    export_product();
                } else if (ch == 0) {
                    printf("Thoat menu nhap/xuat hang.\n");
                    break; 
                } else {
                    printf("Lua chon khong hop le!\n");
                }
            }
            break;
            case 8: show_history(); break;
            case 0: 
                printf("Thoat chuong trinh...\n");
                return 0;
            default:
                printf("Lua chon khong hop le!\n");
        }
    }

    return 0;
}

/*=============== CAC HAM TIEN ICH (DA TOI UU) ===========================*/

/* xoa input buffer an toan */
void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* nhap so nguyen an toan (TOI UU XU LY BUFFER) */
int input_int() {
    char buf[128];
    long val;
    char *endptr;

    while (1) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            clear_input();
            printf("Nhap lai: ");
            continue;
        }

        // Kiem tra buffer tran
        if (buf[strlen(buf) - 1] != '\n') {
            clear_input();
        }

        buf[strcspn(buf, "\n")] = 0; 

        if (is_empty(buf)) {
            printf("Khong duoc de trong. Nhap lai: ");
            continue;
        }

        val = strtol(buf, &endptr, 10);

        if (*endptr != '\0') {
            printf("Vui long nhap so nguyen: ");
            continue;
        }

        return (int)val;
    }
}

/* kiem tra chuoi rong hoac chi toan khoang trang */
int is_empty(const char *s) {
    if (!s) return 1;
    while (*s && isspace((unsigned char)*s)) s++;
    return *s == '\0';
}

/* chuyen chuoi sang chu thuong */
void str_to_lower(char *s) {
    for (int i = 0; s[i]; i++) s[i] = (char)tolower((unsigned char)s[i]);
}

/* lay thoi gian hien tai dang chuoi dd/mm/yyyy hh:mm:ss */
void get_time_str(char *buf, int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    if (t) {
        snprintf(buf, size, "%02d/%02d/%04d %02d:%02d:%02d",
                 t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
                 t->tm_hour, t->tm_min, t->tm_sec);
    } else {
        strncpy(buf, "unknown", size);
        buf[size-1] = '\0';
    }
}

/* ====================== CHUC NANG ============================*/

/* tim index san pham theo productId, tra ve -1 neu khong tim thay */
int find_product_by_id(const char *id) {
    if (!id) return -1;
    for (int i = 0; i < count; i++)
        if (strcmp(list[i].productId, id) == 0)
            return i;
    return -1;
}

/* in mot dong thong tin san pham */
void print_product_row(int i) {
    if (i < 0 || i >= count) return;
    printf("|%-4d|%-10s|%-30.30s|%-8s|%-6d|%-12s|\n",
        i+1, list[i].productId, list[i].name, list[i].unit,
        list[i].qty, (list[i].status ? "Mo" : "Khoa"));
}

/* khoi tao danh sach mau 20 san pham */
void init_list_sample() {
    Product temp[] = {
        {"C001","Banh Mi","Cai",120,1},
        {"C002","Sua Tuoi","Hop",80,1},
        {"C003","Keo Dua","Goi",200,1},
        {"C004","Gao","Kg",50,1},
        {"C005","Duong","Kg",75,1},
        {"C006","Muoi","Kg",40,1},
        {"C007","Nuoc Tuong","Chai",35,1},
        {"C008","Nuoc Mam","Chai",60,1},
        {"C009","Mi Goi","Goi",500,1},
        {"C010","Thit Heo","Kg",30,1},
        {"C011","Thit Bo","Kg",20,1},
        {"C012","Rau Muong","Bo",100,1},
        {"C013","Coca Cola","Lon",150,1},
        {"C014","Pepsi","Lon",140,1},
        {"C015","Tra Xanh","Chai",110,1},
        {"C016","Oreo","Goi",70,1},
        {"C017","Kem Danh Rang","Tuy",55,1},
        {"C018","Bot Giat","Kg",90,1},
        {"C019","Nuoc Rua Chen","Chai",65,1},
        {"C020","Dau Goi","Chai",45,1}
    };

    int n = sizeof(temp) / sizeof(temp[0]);
    if (n > MAX_PRODUCTS) n = MAX_PRODUCTS;
    for (int i = 0; i < n; i++) list[i] = temp[i];
    count = n;
}

/* them san pham moi (TOI UU XU LY BUFFER) */
void add_product() {
    if (count >= MAX_PRODUCTS) {
        printf("Kho da day!\n");
        return;
    }

    char id[16], name[64], unit[16];
    int qty;

    while (1) {
        printf("Nhap ma san pham: ");
        if (!fgets(id, sizeof(id), stdin)) { clear_input(); continue; }
        
        if (id[strlen(id) - 1] != '\n') { clear_input(); }
        
        id[strcspn(id, "\n")] = 0;
        if (is_empty(id)) { printf("Ma san pham khong duoc de trong.\n"); continue; }
        if (find_product_by_id(id) != -1) { printf("Ma san pham da ton tai.\n"); continue; }
        break;
    }

    do {
        printf("Nhap ten san pham: ");
        if (!fgets(name, sizeof(name), stdin)) { clear_input(); continue; }
        
        if (name[strlen(name) - 1] != '\n') { clear_input(); }
        
        name[strcspn(name, "\n")] = 0;
    } while (is_empty(name));

    do {
        printf("Nhap don vi: ");
        if (!fgets(unit, sizeof(unit), stdin)) { clear_input(); continue; }
        
        if (unit[strlen(unit) - 1] != '\n') { clear_input(); }
        
        unit[strcspn(unit, "\n")] = 0;
    } while (is_empty(unit));

    do {
        printf("Nhap so luong (>=0): ");
        qty = input_int();
        if (qty < 0) printf("So luong phai >= 0. Nhap lai.\n");
    } while (qty < 0);

    strncpy(list[count].productId, id, sizeof(list[count].productId)-1);
    list[count].productId[sizeof(list[count].productId)-1] = '\0';
    strncpy(list[count].name, name, sizeof(list[count].name)-1);
    list[count].name[sizeof(list[count].name)-1] = '\0';
    strncpy(list[count].unit, unit, sizeof(list[count].unit)-1);
    list[count].unit[sizeof(list[count].unit)-1] = '\0';
    list[count].qty = qty;
    list[count].status = (qty > 0) ? 1 : 0;
    count++;
    printf("Da them san pham. Tong san pham hien tai: %d\n", count);
}

/* cap nhat thong tin san pham (TOI UU XU LY BUFFER) */
void update_product() {
    if (count == 0) { printf("Danh sach rong.\n"); return; }

    char id[16], name[64], unit[16];
    int pos, qty;

    do {
        printf("Nhap ma hang can cap nhat: ");
        if (!fgets(id, sizeof(id), stdin)) { clear_input(); continue; }
        
        if (id[strlen(id) - 1] != '\n') { clear_input(); }
        
        id[strcspn(id, "\n")] = 0;
    } while (is_empty(id));

    pos = find_product_by_id(id);
    if (pos == -1) { printf("Khong tim thay san pham.\n"); return; }

    printf("--- Thong tin hien tai ---\n");
    print_product_row(pos);

    do {
        printf("Nhap ten moi: ");
        if (!fgets(name, sizeof(name), stdin)) { clear_input(); continue; }
        
        if (name[strlen(name) - 1] != '\n') { clear_input(); }
        
        name[strcspn(name, "\n")] = 0;
    } while (is_empty(name));
    strncpy(list[pos].name, name, sizeof(list[pos].name)-1);
    list[pos].name[sizeof(list[pos].name)-1] = '\0';

    do {
        printf("Nhap don vi moi: ");
        if (!fgets(unit, sizeof(unit), stdin)) { clear_input(); continue; }
        
        if (unit[strlen(unit) - 1] != '\n') { clear_input(); }
        
        unit[strcspn(unit, "\n")] = 0;
    } while (is_empty(unit));
    strncpy(list[pos].unit, unit, sizeof(list[pos].unit)-1);
    list[pos].unit[sizeof(list[pos].unit)-1] = '\0';

    do {
        printf("Nhap so luong moi (>=0): ");
        qty = input_int();
        if (qty < 0) printf("So luong phai >= 0. Nhap lai.\n");
    } while (qty < 0);
    list[pos].qty = qty;
    list[pos].status = (qty > 0) ? 1 : 0;

    printf("Cap nhat thanh cong.\n");
}

/* quan ly trang thai (khoa / mo) (TOI UU XU LY BUFFER) */
void manage_status() {
    if (count == 0) { printf("Danh sach rong.\n"); return; }

    char id[16];
    int pos, action;

    do {
        printf("Nhap productId: ");
        if (!fgets(id, sizeof(id), stdin)) { clear_input(); continue; }
        
        if (id[strlen(id) - 1] != '\n') { clear_input(); }
        
        id[strcspn(id, "\n")] = 0;
    } while (is_empty(id));

    pos = find_product_by_id(id);
    if (pos == -1) { printf("Khong tim thay san pham.\n"); return; }

    printf("San pham: %s (Trang thai: %s)\n", list[pos].name,
           (list[pos].status == 1) ? "Dang mo" : "Da khoa/Het hang");
    printf("1. Khoa san pham\n2. Mo khoa san pham\nLua chon: ");
    action = input_int();
    if (action == 1) {
        if (list[pos].status == 0) printf("San pham da bi khoa.\n");
        else { list[pos].status = 0; printf("Da khoa san pham.\n"); }
    } else if (action == 2) {
        if (list[pos].qty == 0) printf("Khong the mo khoa (SL = 0)!\n");
        else if (list[pos].status == 1) printf("San pham dang mo.\n");
        else { list[pos].status = 1; printf("Da mo khoa san pham.\n"); }
    } else {
        printf("Lua chon khong hop le.\n");
    }
}

/* tim kiem san pham theo id hoac ten (TOI UU XU LY BUFFER) */
void search_products() {
    if (count == 0) { printf("Danh sach rong.\n"); return; }

    char search_id[16], search_name[64];
    int found = 0;

    printf("Nhap productId (co the bo trong): ");
    if (!fgets(search_id, sizeof(search_id), stdin)) { clear_input(); strcpy(search_id, ""); }
    
    if (search_id[strlen(search_id) - 1] != '\n') { clear_input(); }
    
    search_id[strcspn(search_id, "\n")] = 0;

    printf("Nhap ten (co the bo trong): ");
    if (!fgets(search_name, sizeof(search_name), stdin)) { clear_input(); strcpy(search_name, ""); }
    
    if (search_name[strlen(search_name) - 1] != '\n') { clear_input(); }
    
    search_name[strcspn(search_name, "\n")] = 0;

    if (is_empty(search_id) && is_empty(search_name)) {
        printf("Phai nhap it nhat 1 truong!\n");
        return;
    }

    char lower_search_name[64];
    strncpy(lower_search_name, search_name, sizeof(lower_search_name)-1);
    lower_search_name[sizeof(lower_search_name)-1] = '\0';
    str_to_lower(lower_search_name);

    for (int i = 0; i < count; i++) {
        char lower_name[64];
        strncpy(lower_name, list[i].name, sizeof(lower_name)-1);
        lower_name[sizeof(lower_name)-1] = '\0';
        str_to_lower(lower_name);

        int match_id = (is_empty(search_id) || strcmp(list[i].productId, search_id) == 0);
        int match_name = (is_empty(search_name) || strstr(lower_name, lower_search_name) != NULL);

        if (match_id && match_name) {
            if (!found) {
                printf("|%-4s|%-10s|%-30s|%-8s|%-6s|%-12s|\n",
                       "STT", "ProductID", "Ten", "Don vi", "SL", "Trang thai");
            }
            print_product_row(i);
            found = 1;
        }
    }

    if (!found) printf("Khong co ket qua.\n");
}

/* phan trang danh sach san pham (TOI UU XU LY BUFFER) */
void paginate_products() {
    if (count == 0) { printf("Danh sach rong.\n"); return; }
    int per_page = 10;
    int total_page = (count + per_page - 1) / per_page;
    int page = 1;

    while (1) {
        int start = (page - 1) * per_page;
        int end = start + per_page;
        if (end > count) end = count;
        printf("\n--- Trang %d/%d ---\n", page, total_page);
        printf("|%-4s|%-10s|%-30s|%-8s|%-6s|%-12s|\n",
               "STT", "ProductID", "Ten", "Don vi", "SL", "Trang thai");
        for (int i = start; i < end; i++) print_product_row(i);

        printf("\nN: Trang sau | M: Trang truoc | Q: Thoat\nLua chon: ");
        char buf[8];
        if (!fgets(buf, sizeof(buf), stdin)) { clear_input(); continue; }
        
        if (buf[strlen(buf) - 1] != '\n') { clear_input(); }
        
        char c = buf[0];
        if (c == 'N' || c == 'n') {
            if (page < total_page) page++;
            else printf("Trang cuoi.\n");
        } else if (c == 'M' || c == 'm') {
            if (page > 1) page--;
            else printf("Trang dau.\n");
        } else if (c == 'Q' || c == 'q') {
            break;
        } else {
            printf("Lua chon khong hop le.\n");
        }
    }
}

/* sap xep san pham theo tieu chi */
void sort_products_menu() {
    if (count == 0) {
        printf("Danh sach hang hoa rong.\n");
        return;
    }

    printf("Chon tieu chi sap xep:\n");
    printf("1. Ten (A-Z)\n");
    printf("2. So luong (Tang dan)\n");
    printf("Lua chon: ");
    int choice = input_int();

    // sap xep bang Bubble Sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            int swap = 0;
            if (choice == 1) { // sap xep theo ten
                if (strcmp(list[i].name, list[j].name) > 0) swap = 1;
            } else if (choice == 2) { // sap xep theo so luong
                if (list[i].qty > list[j].qty) swap = 1;
            } else {
                printf("Lua chon khong hop le.\n");
                return;
            }

            if (swap) {
                Product tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        }
    }

    printf("Da sap xep thanh cong!\n");
    
    // hien thi danh sach sau khi sap xep (phan trang 10 ban ghi)
    paginate_products(); // Goi lai ham phan trang da toi uu o tren.
}

/* them ban ghi lich su */
void add_history_record(const char *productId, int amount, int type) {
    if (historyCount >= MAX_HISTORY) {
        printf("Chu y: Da dat toi da luu lich su (%d giao dich). Khong luu them.\n", MAX_HISTORY);
        return;
    }
    strncpy(history[historyCount].productId, productId, sizeof(history[historyCount].productId)-1);
    history[historyCount].productId[sizeof(history[historyCount].productId)-1] = '\0';
    history[historyCount].amount = amount;
    history[historyCount].type = type;
    get_time_str(history[historyCount].time, sizeof(history[historyCount].time));
    historyCount++;
}

/* menu nhap hang (import) (TOI UU XU LY BUFFER) */
void import_product() {
    if (count == 0) { printf("Danh sach san pham rong.\n"); return; }

    char id[16];
    int pos, amount;

    while (1) {
        printf("Nhap productId de nhap hang (0 de thoat): ");
        if (!fgets(id, sizeof(id), stdin)) { clear_input(); continue; }
        
        if (id[strlen(id) - 1] != '\n') { clear_input(); }
        
        id[strcspn(id, "\n")] = 0;

        if (strcmp(id, "0") == 0) return; 
        if (is_empty(id)) continue;

        pos = find_product_by_id(id);
        if (pos == -1) { printf("Khong tim thay san pham.\n"); continue; }

        do {
            printf("Nhap so luong nhap (>0, 0 de thoat): ");
            amount = input_int();
            if (amount == 0) return; 
            if (amount < 0) printf("So luong phai > 0. Nhap lai.\n");
        } while (amount <= 0);

        list[pos].qty += amount;
        list[pos].status = 1;
        add_history_record(id, amount, 1);
        printf("Nhap hang thanh cong. SL hien tai: %d\n", list[pos].qty);
        break;
    }
}

/* menu xuat hang (export) (TOI UU XU LY BUFFER) */
void export_product() {
    if (count == 0) { printf("Danh sach san pham rong.\n"); return; }

    char id[16];
    int pos, amount;

    while (1) {
        printf("Nhap productId de xuat hang (0 de thoat): ");
        if (!fgets(id, sizeof(id), stdin)) { clear_input(); continue; }
        
        if (id[strlen(id) - 1] != '\n') { clear_input(); }
        
        id[strcspn(id, "\n")] = 0;

        if (strcmp(id, "0") == 0) return; 
        if (is_empty(id)) continue;

        pos = find_product_by_id(id);
        if (pos == -1) { printf("Khong tim thay san pham.\n"); continue; }

        if (list[pos].status == 0) { printf("San pham dang khoa/het hang.\n"); continue; }

        do {
            printf("Nhap so luong xuat (<= %d, 0 de thoat): ", list[pos].qty);
            amount = input_int();
            if (amount == 0) return; 
            if (amount < 0 || amount > list[pos].qty) printf("So luong khong hop le. Nhap lai.\n");
        } while (amount <= 0 || amount > list[pos].qty);

        list[pos].qty -= amount;
        if (list[pos].qty == 0) list[pos].status = 0;
        add_history_record(id, amount, 2);
        printf("Xuat hang thanh cong. SL hien tai: %d\n", list[pos].qty);
        break;
    }
}

/* hien thi lich su giao dich */
void show_history() {
    if (historyCount == 0) { printf("Chua co giao dich nao.\n"); return; }
    printf("\n===== LICH SU GIAO DICH =====\n");
    printf("|%-4s|%-12s|%-10s|%-10s|%-20s|\n", "STT", "ProductID", "Loai", "So luong", "Thoi gian");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < historyCount; i++) {
        printf("|%-4d|%-12s|%-10s|%-10d|%-20s|\n",
               i + 1,
               history[i].productId,
               (history[i].type == 1) ? "Nhap" : "Xuat",
               history[i].amount,
               history[i].time);
    }
    printf("-----------------------------------------------------------\n");
}
