#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char productId[10];
    char name[50];
    char unit[10];
    int qty;
    int status; // 1: con hang, 0: het hang
} Product;

Product list[MAX];
int count = 0;

// ham kiem tra chuoi rong hoac chi co khoang trang
int is_empty(const char *str){
    if(!str) return 1;
    while(*str){
        if(!isspace((unsigned char)*str)) return 0;
        str++;
    }
    return 1;
}

int main() {
    int choice, i, pos;
    char temp_id[10], temp_name[50], temp_unit[10];
    int temp_qty;

    do {
    printf("\n==========================================\n");
    printf("|               MENU                     |\n");
    printf("|========================================|\n");
    printf("| 1. Them ma hang moi                    |\n");
    printf("| 2. Cap nhat thong tin                  |\n");
    printf("| 3. Quan li trang thai                  |\n");
    printf("| 4. Tra cuu                             |\n");
    printf("| 5. Danh sach                           |\n");
    printf("| 6. Danh sach sap xep                   |\n");
    printf("| 7. Giao dich xuat/nhap khau hang hoa   |\n");
    printf("| 8. Lich su xuat/nhap                   |\n");
    printf("| 0. Thoat                               |\n");
    printf("|========================================|\n");
    printf(" Lua chon:\n ");
    scanf("%d", &choice);
    getchar();
        switch(choice) {

            case 1: // Them san pham
                if(count >= MAX) {
                    printf("Danh sach da day!\n");
                    break;
                }

                // Nhap ma hang
                do {
                    printf("Nhap ma hang: ");
                    fgets(temp_id, sizeof(temp_id), stdin);
                    temp_id[strcspn(temp_id, "\n")] = 0;
                    if(is_empty(temp_id)) printf("Loi! Ma hang khong duoc de trong!\n");
                } while(is_empty(temp_id));

                // Kiem tra trung ma hang
                for(i = 0; i < count; i++)
                    if(strcmp(list[i].productId, temp_id) == 0){
                        printf(" Ma hang da ton tai!\n");
                        goto end_case1;
                    }

                strcpy(list[count].productId, temp_id);

                // Nhap ten
                do {
                    printf("Nhap ten hang: ");
                    fgets(temp_name, sizeof(temp_name), stdin);
                    temp_name[strcspn(temp_name, "\n")] = 0;
                    if(is_empty(temp_name)) printf("Loi! Ten hang khong duoc de trong!\n");
                } while(is_empty(temp_name));
                strcpy(list[count].name, temp_name);

                // Nhap don vi
                do {
                    printf("Nhap don vi: ");
                    fgets(temp_unit, sizeof(temp_unit), stdin);
                    temp_unit[strcspn(temp_unit, "\n")] = 0;
                    if(is_empty(temp_unit)) printf("Loi! Don vi khong duoc de trong!\n");
                } while(is_empty(temp_unit));
                strcpy(list[count].unit, temp_unit);

                // Nhap so luong
                do {
            char buffer[20];
            printf("Nhap so luong: ");
            if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
            temp_qty = -1;
            continue;
    }
            buffer[strcspn(buffer, "\n")] = 0; // xoa newline
            if(strlen(buffer) == 0) {
            printf("Loi! So luong khong duoc de trong!\n");
            temp_qty = -1;
            continue;
    }
            if(sscanf(buffer, "%d", &temp_qty) != 1) {
            printf(" Phai nhap so!\n");
            temp_qty = -1;
            continue;
        }
            if(temp_qty < 0) {
            printf(" So luong phai >=0\n");
            temp_qty = -1;
            continue;
        }
        } while(temp_qty < 0);
                getchar();
                list[count].qty = temp_qty;
                list[count].status = (temp_qty > 0) ? 1 : 0;

                count++;
                printf("Da them san pham!\n");
                for(i = 0; i < count; i++)
                    printf("[%d] ID:%s Ten:%s Don vi:%s SL:%d Status:%d\n",
                        i+1, list[i].productId, list[i].name,
                        list[i].unit, list[i].qty, list[i].status);

                end_case1:
                break;

            case 2: // Cap nhat san pham
                // Nhap ma hang can cap nhat
                do {
                    printf("Nhap ma hang can cap nhat: ");
                    fgets(temp_id, sizeof(temp_id), stdin);
                    temp_id[strcspn(temp_id, "\n")] = 0;
                    if(is_empty(temp_id)) printf("Loi! Ma hang khong duoc de trong!\n");
                } while(is_empty(temp_id));

                pos = -1;
                for(i = 0; i < count; i++)
                    if(strcmp(list[i].productId, temp_id) == 0) pos = i;
                if(pos == -1) {
                    printf("Khong tim thay san pham!\n");
                    break;
                }

                // Nhap ten moi
                do {
                    printf("Nhap ten moi: ");
                    fgets(temp_name, sizeof(temp_name), stdin);
                    temp_name[strcspn(temp_name, "\n")] = 0;
                    if(is_empty(temp_name)) printf("Loi! Ten hang khong duoc de trong!\n");
                } while(is_empty(temp_name));
                strcpy(list[pos].name, temp_name);

                // Nhap don vi moi
                do {
                    printf("Nhap don vi moi: ");
                    fgets(temp_unit, sizeof(temp_unit), stdin);
                    temp_unit[strcspn(temp_unit, "\n")] = 0;
                    if(is_empty(temp_unit)) printf("Loi! Don vi khong duoc de trong!\n");
                } while(is_empty(temp_unit));
                strcpy(list[pos].unit, temp_unit);

                // Nhap so luong moi
                do {
                    printf("Nhap so luong moi: ");
                    if(scanf("%d", &temp_qty) != 1){
                        printf("Phai nhap so!\n");
                        while(getchar() != '\n');
                        temp_qty = -1;
                    }
                    else if(temp_qty < 0) printf("Loi!: So luong phai >=0\n");
                } while(temp_qty < 0);
                getchar();
                list[pos].qty = temp_qty;
                list[pos].status = (temp_qty > 0) ? 1 : 0;

                printf("Da cap nhat san pham!\n");
                for(i = 0; i < count; i++)
                    printf("[%d] ID:%s Ten:%s Don vi:%s SL:%d Status:%d\n",
                        i+1, list[i].productId, list[i].name,
                        list[i].unit, list[i].qty, list[i].status);
                break;
            case 3: {
                char temp_id[10];
                int found = 0;

            // Nhap productId
        do {
               printf("Nhap productId can khoa: ");
            if(fgets(temp_id, sizeof(temp_id), stdin) == NULL) break;
                temp_id[strcspn(temp_id, "\n")] = 0; // xoa newline
            if(strlen(temp_id) == 0) {
            printf("Loi! productId khong duoc de trong.\n");
        }
            } while(strlen(temp_id) == 0);

            if(strlen(temp_id) == 0) break; // nguoi dung bam Enter lien tiep

            // Tim san pham
            int i;
               for( i = 0; i < count; i++) {
            if(strcmp(list[i].productId, temp_id) == 0) {
               found = 1;
            if(list[i].status == 0) {
                printf("San pham da bi khoa.\n");
            } else {
                list[i].status = 0;
                printf("San pham %s da duoc khoa thanh cong.\n", list[i].name);
            }
            break;
        }
    }
    if(!found) {
        printf("Khong tim thay san pham voi productId: %s\n", temp_id);
        }   
            break;
    } 
            case 4: {
            	char search_id[10], search_name[50];
                int found = 0;

            // Nhap productId (co the bo trong)
                printf("Nhap productId can tim (de trong neu muon bo qua): ");
            if(fgets(search_id, sizeof(search_id), stdin) == NULL) break;
                search_id[strcspn(search_id, "\n")] = 0; // xoa newline

            // Nhap ten hang (co the bo trong)
               printf("Nhap ten hang can tim (de trong neu muon bo qua): ");
            if(fgets(search_name, sizeof(search_name), stdin) == NULL) break;
               search_name[strcspn(search_name, "\n")] = 0; // xoa newline

            // Kiem tra: ca hai khong duoc de trong
            if(strlen(search_id) == 0 && strlen(search_name) == 0) {
                printf("Error: Phai nhap productId hoac ten hang de tim kiem.\n");
                break;
        }
                printf("\n--- Ket qua tim kiem ---\n");
                int i;
                for( i = 0; i < count; i++) {
            // Tim theo productId chinh xac hoac ten gan dung
            if((strlen(search_id) > 0 && strcmp(list[i].productId, search_id) == 0) ||
               (strlen(search_name) > 0 && strstr(list[i].name, search_name) != NULL)) {
                found = 1;
                printf("[%d] ID:%s Ten:%s Don vi:%s SL:%d Status:%d\n",
                i+1, list[i].productId, list[i].name,
                list[i].unit, list[i].qty, list[i].status);
        }
    }

    if(!found) {
        printf("Loi! Khong tim thay san pham phu hop.\n");
    }
				break;
			}
            case 0:
                printf("Thoat chuong trinh.\n");
                break;

            default:
                printf("Lua chon khong hop le.\n");
        }

    } while(choice != 0);

    return 0;
}

