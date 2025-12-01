#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PRODUCTS 100   // so luong toi da san pham
#define MAX_HISTORY 500    // so luong toi da lich su giao dich

// cau truc luu thong tin san pham
typedef struct {
    char productId[10];    // ma san pham
    char name[50];         // ten san pham
    char unit[10];         // don vi tinh
    int qty;               // so luong hien tai
    int status;            /* 1: con hang / mo khoa, 0: het hang / bi khoa */
} Product;

// cau truc luu lich su giao dich
typedef struct {
    char productId[10];    // ma san pham
    int amount;            // so luong nhap/xuat
    int type;              /* 1 = IN (nhap), 2 = OUT (xuat) */
    char time[30];         // thoi gian giao dich
} Transaction;
    // --- Nguyen ham mau ---
void clear_input();
int is_empty(const char *str);
int input_int();
void str_to_lower(char *str);
int find_product_by_id(const char *product_id);
void print_product_row(int index);
void init_list();
void get_time_str(char *buf, int size);

Product list[MAX_PRODUCTS];   // mang luu danh sach san pham
Transaction history[MAX_HISTORY]; // mang luu lich su giao dich
int count = 20;               // so san pham hien co
int historyCount = 0;         // so giao dich da thuc hien

// xoa buffer input de tranh loi nhap sai
void clear_input() {
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

// kiem tra chuoi rong hoac chi chua khoang trang
int is_empty(const char *str) {
    if(!str) return 1;
    while(*str && isspace((unsigned char)*str)) str++;
    return *str == '\0';
}

// nhap so nguyen an toan, kiem tra hop le
int input_int() {
    char buffer[50];
    long num;
    char *endptr;
    while(1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;
        buffer[strcspn(buffer, "\n")] = 0;
        if(is_empty(buffer)) { printf("Khong duoc de trong! Nhap lai: "); continue; }
        num = strtol(buffer, &endptr, 10);
        if(*endptr != '\0' && !isspace((unsigned char)*endptr)) {
            printf("Vui long nhap so nguyen hop le: "); continue;
        }
        return (int)num;
    }
}

// chuyen chuoi thanh chu thuong
void str_to_lower(char *str) {
    for(int i=0; str[i]; i++) str[i] = tolower((unsigned char)str[i]);
}

// tim san pham theo ma, tra ve vi tri, -1 neu khong tim thay
int find_product_by_id(const char *product_id) {
    for(int i=0;i<count;i++)
        if(strcmp(list[i].productId, product_id)==0) return i;
    return -1;
}

// in 1 dong thong tin san pham
void print_product_row(int index) {
    printf("|%-5d|%-10s|%-20.20s|%-10s|%-5d|%-15s|\n",
        index+1,
        list[index].productId,
        list[index].name,
        list[index].unit,
        list[index].qty,
        (list[index].status==1)?"Con su dung":"Het hang/Khoa");
}

// khoi tao danh sach san pham mac dinh
void init_list() {
    Product temp[20] = {
        {"C001", "Banh Mi", "Cai", 120, 1},
        {"C002", "Sua Tuoi", "Hop", 80, 1},
        {"C003", "Keo Dua", "Goi", 200, 1},
        {"C004", "Gao Thom", "Kg", 50, 1},
        {"C005", "Duong Trang", "Kg", 75, 1},
        {"C006", "Muoi Iot", "Kg", 40, 1},
        {"C007", "Nuoc Tuong", "Chai", 35, 1},
        {"C008", "Nuoc Mam", "Chai", 60, 1},
        {"C009", "Mi Goi", "Goi", 500, 1},
        {"C010", "Thit Heo", "Kg", 30, 1},
        {"C011", "Thit Bo", "Kg", 20, 1},
        {"C012", "Rau Muong", "Bo", 100, 1},
        {"C013", "Coca Cola", "Lon", 150, 1},
        {"C014", "Pepsi", "Lon", 140, 1},
        {"C015", "Tra Xanh", "Chai", 110, 1},
        {"C016", "Banh Oreo", "Goi", 70, 1},
        {"C017", "Kem Danh Rang", "Tuy", 55, 1},
        {"C018", "Bot Giat OMO", "Kg", 90, 1},
        {"C019", "Nuoc Rua Chen", "Chai", 65, 1},
        {"C020", "Dau Goi Dau", "Chai", 45, 1}
    };
    for(int i=0;i<count;i++) list[i]=temp[i];
}

// lay thoi gian hien tai duoi dang chuoi
void get_time_str(char *buf, int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    if(t) {
        snprintf(buf, size, "%02d/%02d/%04d %02d:%02d:%02d",
            t->tm_mday, t->tm_mon+1, t->tm_year+1900,
            t->tm_hour, t->tm_min, t->tm_sec);
    } else {
        strncpy(buf, "unknown", size);
        buf[size-1] = '\0';
    }
}

// --- ham main ---
int main() {
    init_list();   // khoi tao danh sach san pham
    int choice;

    do {
        // hien thi menu chinh
        printf("\n==========================================\n");
        printf("|          MENU QUAN LY KHO              |\n");
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

        choice = input_int(); // nhap lua chon
        char temp_id[10], temp_name[50], temp_unit[10];
        int temp_qty, pos;

        switch(choice) {

            case 1: // them san pham moi
                if(count>=MAX_PRODUCTS){ printf("Loi: Danh sach day!\n"); break; }

                // nhap ma hang
                while(1){
                    printf("Nhap ma hang: ");
                    if(!fgets(temp_id,sizeof(temp_id),stdin)) continue;
                    temp_id[strcspn(temp_id,"\n")]=0;
                    if(is_empty(temp_id)) { printf("Khong duoc de trong!\n"); continue; }
                    if(find_product_by_id(temp_id)!=-1) { printf("Ma hang da ton tai!\n"); continue; }
                    break;
                }
                strcpy(list[count].productId,temp_id);

                // nhap ten hang
                do{
                    printf("Nhap ten hang: ");
                    if(!fgets(temp_name,sizeof(temp_name),stdin)) continue;
                    temp_name[strcspn(temp_name,"\n")]=0;
                    if(is_empty(temp_name)) printf("Ten hang khong duoc de trong!\n");
                } while(is_empty(temp_name));
                strcpy(list[count].name,temp_name);

                // nhap don vi
                do{
                    printf("Nhap don vi: ");
                    if(!fgets(temp_unit,sizeof(temp_unit),stdin)) continue;
                    temp_unit[strcspn(temp_unit,"\n")]=0;
                    if(is_empty(temp_unit)) printf("Don vi khong duoc de trong!\n");
                } while(is_empty(temp_unit));
                strcpy(list[count].unit,temp_unit);

                // nhap so luong
                do{
                    printf("Nhap so luong (>=0): ");
                    temp_qty = input_int();
                    if(temp_qty<0) printf("So luong phai >=0!\n");
                } while(temp_qty<0);

                list[count].qty=temp_qty;
                list[count].status=(temp_qty>0)?1:0;
                count++;
                printf("Da them san pham moi! Tong san pham: %d\n",count);
                break;

            case 2: // cap nhat thong tin san pham
                if(count==0){ printf("Danh sach rong!\n"); break; }
                do{
                    printf("Nhap ma hang can cap nhat: ");
                    if(!fgets(temp_id,sizeof(temp_id),stdin)) continue;
                    temp_id[strcspn(temp_id,"\n")]=0;
                    if(is_empty(temp_id)) printf("Ma hang khong duoc de trong!\n");
                } while(is_empty(temp_id));

                pos=find_product_by_id(temp_id);
                if(pos==-1){ printf("Khong tim thay san pham!\n"); break; }

                printf("--- Thong tin hien tai ---\n");
                print_product_row(pos);

                // cap nhat ten
                do{
                    printf("Nhap ten moi: ");
                    if(!fgets(temp_name,sizeof(temp_name),stdin)) continue;
                    temp_name[strcspn(temp_name,"\n")]=0;
                    if(is_empty(temp_name)) printf("Ten khong duoc rong!\n");
                } while(is_empty(temp_name));
                strcpy(list[pos].name,temp_name);

                // cap nhat don vi
                do{
                    printf("Nhap don vi moi: ");
                    if(!fgets(temp_unit,sizeof(temp_unit),stdin)) continue;
                    temp_unit[strcspn(temp_unit,"\n")]=0;
                    if(is_empty(temp_unit)) printf("Don vi khong duoc rong!\n");
                } while(is_empty(temp_unit));
                strcpy(list[pos].unit,temp_unit);

                // cap nhat so luong
                do{
                    printf("Nhap so luong moi (>=0): ");
                    temp_qty=input_int();
                    if(temp_qty<0) printf("So luong phai >=0!\n");
                } while(temp_qty<0);
                list[pos].qty=temp_qty;
                list[pos].status=(temp_qty>0)?1:0;

                printf("Da cap nhat thanh cong!\n");
                break;

            case 3: // quan ly trang thai san pham
                if(count==0){ printf("Danh sach rong!\n"); break; }
                do{
                    printf("Nhap productId: ");
                    if(!fgets(temp_id,sizeof(temp_id),stdin)) continue;
                    temp_id[strcspn(temp_id,"\n")]=0;
                } while(is_empty(temp_id));

                pos=find_product_by_id(temp_id);
                if(pos==-1){ printf("Khong tim thay san pham!\n"); break; }

                printf("San pham: %s (Trang thai: %s)\n",
                    list[pos].name,(list[pos].status==1)?"Dang mo":"Da khoa/Het hang");
                printf("1. Khoa san pham\n2. Mo khoa san pham\nLua chon: ");
                {
                    int action=input_int();
                    if(action==1){
                        if(list[pos].status==0) printf("San pham da bi khoa!\n");
                        else { list[pos].status=0; printf("Da khoa san pham.\n"); }
                    } else if(action==2){
                        if(list[pos].qty==0) printf("Khong the mo khoa (SL=0)!\n");
                        else if(list[pos].status==1) printf("San pham dang mo.\n");
                        else { list[pos].status=1; printf("Da mo khoa san pham.\n"); }
                    } else printf("Lua chon khong hop le!\n");
                }
                break;

            case 4: // tra cuu san pham
                if(count==0){ printf("Danh sach rong!\n"); break; }
                {
                    char search_id[10], search_name[50];
                    int found=0;
                    printf("Nhap productId (co the bo trong): "); fgets(search_id,sizeof(search_id),stdin);
                    search_id[strcspn(search_id,"\n")]=0;
                    printf("Nhap ten (co the bo trong): "); fgets(search_name,sizeof(search_name),stdin);
                    search_name[strcspn(search_name,"\n")]=0;

                    char lower_search_name[50]; strcpy(lower_search_name,search_name); str_to_lower(lower_search_name);

                    if(is_empty(search_id) && is_empty(search_name)){ printf("Phai nhap it nhat 1 truong!\n"); break; }

                    printf("\n--- Ket qua tim kiem ---\n");
                    for(int i=0;i<count;i++){
                        char lower_name[50]; strcpy(lower_name,list[i].name); str_to_lower(lower_name);
                        int match_id=(is_empty(search_id)||strcmp(list[i].productId,search_id)==0);
                        int match_name=(is_empty(search_name)||strstr(lower_name,lower_search_name));
                        if(match_id && match_name){
                            if(!found) printf("|%-5s|%-10s|%-20s|%-10s|%-5s|%-15s|\n","STT","ProductID","Ten","Don vi","SL","Trang thai");
                            print_product_row(i);
                            found=1;
                        }
                    }
                    if(!found) printf("Khong co ket qua.\n");
                }
                break;

            case 5: // phan trang danh sach
                if(count==0){ printf("Danh sach rong!\n"); break; }
                {
                    int page=1, per_page=10, total_page=(count+per_page-1)/per_page;
                    char temp;
                    do{
                        int start=(page-1)*per_page, end=start+per_page; if(end>count) end=count;
                        printf("\n--- Trang %d/%d ---\n",page,total_page);
                        printf("|%-5s|%-10s|%-20s|%-10s|%-5s|%-15s|\n","STT","ProductID","Ten","Don vi","SL","Trang thai");
                        for(int i=start;i<end;i++) print_product_row(i);
                        printf("\nN: Trang sau | M: Trang truoc | Q: Thoat\nLua chon: ");
                        temp=getchar(); clear_input();
                        if(temp=='N'||temp=='n'){ if(page<total_page) page++; else printf("Trang cuoi.\n"); }
                        else if(temp=='M'||temp=='m'){ if(page>1) page--; else printf("Trang dau.\n"); }
                        else if(temp=='Q'||temp=='q') break;
                        else printf("Lua chon khong hop le!\n");
                    } while(1);
                }
                break;

            case 6: // sap xep danh sach
                if(count==0){ printf("Danh sach rong!\n"); break; }
                {
                    char type[10];
                    printf("Nhap 'TEN' de sap xep theo ten (A-Z), 'SL' theo so luong tang dan, 'Q' thoat: ");
                    if(!fgets(type,sizeof(type),stdin)) break;
                    type[strcspn(type,"\n")]=0; str_to_lower(type);
                    if(strcmp(type,"q")==0) break;

                    int mode=-1;
                    if(strcmp(type,"ten")==0) mode=1;
                    else if(strcmp(type,"sl")==0) mode=2;
                    else { printf("Lua chon khong hop le!\n"); break; }

                    for(int i=0;i<count-1;i++)
                        for(int j=i+1;j<count;j++){
                            int swap=0;
                            if(mode==1 && strcmp(list[i].name,list[j].name)>0) swap=1;
                            else if(mode==2 && list[i].qty>list[j].qty) swap=1;
                            if(swap){ Product tmp=list[i]; list[i]=list[j]; list[j]=tmp; }
                        }

                    printf("--- Danh sach sau khi sap xep ---\n");
                    printf("|%-5s|%-10s|%-20s|%-10s|%-5s|%-15s|\n","STT","ProductID","Ten","Don vi","SL","Trang thai");
                    for(int i=0;i<count;i++) print_product_row(i);
                }
                break;

            case 7: // giao dich nhap/xuat
                {
                    char id[10];
                    int amount;
                    int opt;

                    do {
                        printf("\n--- GIAO DICH XUAT / NHAP HANG HOA ---\n");
                        printf("1. Nhap hang\n");
                        printf("2. Xuat hang\n");
                        printf("0. Thoat\n");
                        printf("Lua chon: ");
                        opt = input_int();

                        if(opt == 0) break;

                        printf("Nhap productId: ");
                        if(!fgets(id, sizeof(id), stdin)) continue;
                        id[strcspn(id, "\n")] = 0;

                        int p = find_product_by_id(id);
                        if(p == -1) {
                            printf("Khong tim thay san pham!\n");
                            continue;
                        }

                        if(opt == 1) { // nhap hang
                            do {
                                printf("Nhap so luong nhap (>0): ");
                                amount = input_int();
                                if(amount <= 0) printf("So luong phai > 0!\n");
                            } while(amount <= 0);

                            list[p].qty += amount;
                            list[p].status = 1;

                            if(historyCount < MAX_HISTORY) {
                                strcpy(history[historyCount].productId, id);
                                history[historyCount].amount = amount;
                                history[historyCount].type = 1;
                                get_time_str(history[historyCount].time, sizeof(history[historyCount].time));
                                historyCount++;
                            }

                            printf("Nhap hang thanh cong. SL hien tai: %d\n", list[p].qty);

                        } else if(opt == 2) { // xuat hang
                            if(list[p].status == 0) { printf("San pham bi khoa/het hang!\n"); continue; }
                            do {
                                printf("Nhap so luong xuat (<= %d): ", list[p].qty);
                                amount = input_int();
                                if(amount <= 0 || amount > list[p].qty) printf("So luong khong hop le!\n");
                            } while(amount <= 0 || amount > list[p].qty);

                            list[p].qty -= amount;
                            if(list[p].qty==0) list[p].status=0;

                            if(historyCount < MAX_HISTORY) {
                                strcpy(history[historyCount].productId, id);
                                history[historyCount].amount = amount;
                                history[historyCount].type = 2;
                                get_time_str(history[historyCount].time, sizeof(history[historyCount].time));
                                historyCount++;
                            }

                            printf("Xuat hang thanh cong. SL hien tai: %d\n", list[p].qty);
                        } else printf("Lua chon khong hop le!\n");

                    } while(opt != 0);
                }
                break;

            case 8: // lich su xuat nhap
                if(historyCount==0){ printf("Chua co giao dich nao!\n"); break; }
                printf("\n--- LICH SU GIAO DICH ---\n");
                printf("|%-5s|%-10s|%-10s|%-10s|\n","STT","ProductID","Loai","So luong");
                for(int i=0;i<historyCount;i++){
                    printf("|%-5d|%-10s|%-10s|%-10d|\n",i+1,
                        history[i].productId,
                        (history[i].type==1)?"Nhap":"Xuat",
                        history[i].amount);
                }
                break;

            case 0: printf("Thoat chuong trinh!\n"); break;

            default: printf("Lua chon khong hop le!\n");
        }

    } while(choice !=0);

    return 0;
}

