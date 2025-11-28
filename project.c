#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PRODUCTS 100

typedef struct {
    char productId[10];
    char name[50];
    char unit[10];
    int qty;
    int status; // 1: con hang/mo khoa, 0: het hang/bi khoa
} Product;

Product list[MAX_PRODUCTS];
int count = 20;

// --- KHAI BAO HAM HANG CHUNG ---
void clear_input() {
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

int is_empty(const char *str) {
    if(!str) return 1;
    while(*str && isspace((unsigned char)*str)) str++;
    return *str == '\0';
}

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

void str_to_lower(char *str) {
    for(int i=0; str[i]; i++) str[i] = tolower((unsigned char)str[i]);
}

int find_product_by_id(const char *product_id) {
    for(int i=0;i<count;i++)
        if(strcmp(list[i].productId, product_id)==0) return i;
    return -1;
}

void print_product_row(int index) {
    printf("|%-5d|%-10s|%-20.20s|%-10s|%-5d|%-15s|\n",
        index+1,
        list[index].productId,
        list[index].name,
        list[index].unit,
        list[index].qty,
        (list[index].status==1)?"Con su dung":"Het hang/Khoa");
}

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

// --- MAIN ---
int main() {
    init_list();
    int choice;

    do {
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

        choice = input_int();
        char temp_id[10], temp_name[50], temp_unit[10];
        int temp_qty, pos;

        switch(choice) {
            case 1: // Them san pham moi
                if(count>=MAX_PRODUCTS){ printf("Loi: Danh sach day!\n"); break; }

                // Nhap ma hang
                while(1){
                    printf("Nhap ma hang: ");
                    if(!fgets(temp_id,sizeof(temp_id),stdin)) continue;
                    temp_id[strcspn(temp_id,"\n")]=0;
                    if(is_empty(temp_id)) { printf("Khong duoc de trong!\n"); continue; }
                    if(find_product_by_id(temp_id)!=-1) { printf("Ma hang da ton tai!\n"); continue; }
                    break;
                }
                strcpy(list[count].productId,temp_id);

                // Nhap ten hang
                do{ 
                    printf("Nhap ten hang: "); 
                    if(!fgets(temp_name,sizeof(temp_name),stdin)) continue;
                    temp_name[strcspn(temp_name,"\n")]=0;
                    if(is_empty(temp_name)) printf("Ten hang khong duoc de trong!\n");
                } while(is_empty(temp_name));
                strcpy(list[count].name,temp_name);

                // Nhap don vi
                do{
                    printf("Nhap don vi: ");
                    if(!fgets(temp_unit,sizeof(temp_unit),stdin)) continue;
                    temp_unit[strcspn(temp_unit,"\n")]=0;
                    if(is_empty(temp_unit)) printf("Don vi khong duoc de trong!\n");
                } while(is_empty(temp_unit));
                strcpy(list[count].unit,temp_unit);

                // Nhap so luong
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

            case 2: // Cap nhat
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

                // Cap nhat ten
                do{ 
                    printf("Nhap ten moi: ");
                    if(!fgets(temp_name,sizeof(temp_name),stdin)) continue;
                    temp_name[strcspn(temp_name,"\n")]=0;
                    if(is_empty(temp_name)) printf("Ten khong duoc rong!\n");
                } while(is_empty(temp_name));
                strcpy(list[pos].name,temp_name);

                // Cap nhat don vi
                do{
                    printf("Nhap don vi moi: ");
                    if(!fgets(temp_unit,sizeof(temp_unit),stdin)) continue;
                    temp_unit[strcspn(temp_unit,"\n")]=0;
                    if(is_empty(temp_unit)) printf("Don vi khong duoc rong!\n");
                } while(is_empty(temp_unit));
                strcpy(list[pos].unit,temp_unit);

                // Cap nhat so luong
                do{
                    printf("Nhap so luong moi (>=0): ");
                    temp_qty=input_int();
                    if(temp_qty<0) printf("So luong phai >=0!\n");
                } while(temp_qty<0);
                list[pos].qty=temp_qty;
                list[pos].status=(temp_qty>0)?1:0;

                printf("Da cap nhat thanh cong!\n");
                break;

            case 3: // Quan ly trang thai
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
                int action=input_int();
                if(action==1){
                    if(list[pos].status==0) printf("San pham da bi khoa!\n");
                    else { list[pos].status=0; printf("Da khoa san pham.\n"); }
                } else if(action==2){
                    if(list[pos].qty==0) printf("Khong the mo khoa (SL=0)!\n");
                    else if(list[pos].status==1) printf("San pham dang mo.\n");
                    else { list[pos].status=1; printf("Da mo khoa san pham.\n"); }
                } else printf("Lua chon khong hop le!\n");
                break;

            case 4: // Tra cuu
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

            case 5: // Phan trang
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

            case 6: // Sap xep
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
                case 7: {
					break;
				}
				case 8: {
					break;
				}
            case 0: {
            	printf("Thoat chuong trinh.\n"); 
				break;
				default: printf("Lua chon khong hop le!\n");
			}
            
        }

    } while(choice!=0);

    return 0;
}

