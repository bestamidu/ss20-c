#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

typedef struct {
    char maSach[10];
    char tenSach[50];
    char tacGia[50];
    float gia;
} Sach;

void nhapSach(Sach *sach) {
    printf("Nhap ma sach: ");
    scanf(" %[^\n]s", sach->maSach);
    printf("Nhap ten sach: ");
    scanf(" %[^\n]s", sach->tenSach);
    printf("Nhap tac gia: ");
    scanf(" %[^\n]s", sach->tacGia);
    printf("Nhap gia: ");
    scanf("%f", &sach->gia);
}

void hienThiSach(Sach sach) {
    printf("Ma sach: %s\n", sach.maSach);
    printf("Ten sach: %s\n", sach.tenSach);
    printf("Tac gia: %s\n", sach.tacGia);
    printf("Gia: %.2f\n", sach.gia);
}

int timKiemSachTheoMa(Sach *arr, int n, char *maSach) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].maSach, maSach) == 0) {
            return i;
        }
    }
    return -1;
}


void xoaSachTheoMa(Sach *arr, int *n, char *maSach) {
    int index = timKiemSachTheoMa(arr, *n, maSach);
    if (index != -1) {
        for (int i = index; i < *n - 1; i++) {
            arr[i] = arr[i + 1];
        }
        (*n)--;
        printf("Da xoa sach co ma %s.\n", maSach);
    } else {
        printf("Khong tim thay sach co ma %s.\n", maSach);
    }
}


void capNhatSachTheoMa(Sach *arr, int n, char *maSach) {
    int index = timKiemSachTheoMa(arr, n, maSach);
    if (index != -1) {
        printf("Nhap thong tin sach moi:\n");
        nhapSach(&arr[index]);
        printf("Da cap nhat thong tin sach co ma %s.\n", maSach);
    } else {
        printf("Khong tim thay sach co ma %s.\n", maSach);
    }
}


void sapXepSachTheoGiaTangDan(Sach *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].gia > arr[j + 1].gia) {
                Sach temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void sapXepSachTheoGiaGiamDan(Sach *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].gia < arr[j + 1].gia) {
                Sach temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void timKiemSachTheoTen(Sach *arr, int n, char *tenSach) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(arr[i].tenSach, tenSach) != NULL) {
            hienThiSach(arr[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay sach co ten %s.\n", tenSach);
    }
}

int main() {
    Sach arr[MAX_BOOKS];
    int n = 0, choice;
    char maSach[10], tenSach[50];

    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin sach.\n");
        printf("2. Hien thi thong tin sach.\n");
        printf("3. Them sach vao vi tri.\n");
        printf("4. Xoa sach theo ma sach.\n");
        printf("5. Cap nhat thong tin sach theo ma sach.\n");
        printf("6. Sap xep sach theo gia(tang/giam).\n");
        printf("7. Tim kiem sach theo ten sach.\n");
        printf("8. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap so luong sach: ");
                scanf("%d", &n);
                printf("Nhap thong tin sach:\n");
                for (int i = 0; i < n; i++) {
                    nhapSach(&arr[i]);
                }
                break;
            case 2:
                printf("Thong tin sach:\n");
                for (int i = 0; i < n; i++) {
                    hienThiSach(arr[i]);
                    printf("\n");
                }
                break;
            case 3:
                {
                    int viTri;
                    printf("Nhap vi tri muon them sach (0-%d): ", n);
                    scanf("%d", &viTri);
                    if (viTri >= 0 && viTri <= n) {
                        nhapSach(&arr[n]);
                        for (int i = n; i > viTri; i--) {
                            arr[i] = arr[i - 1];
                        }
                        arr[viTri] = arr[n];
                        n++;
                        printf("Da them sach vao vi tri %d.\n", viTri);
                    } else {
                        printf("Vi tri khong hop le.\n");
                    }
                }
                break;
            case 4:
                printf("Nhap ma sach can xoa: ");
                scanf(" %[^\n]s", maSach);
                xoaSachTheoMa(arr, &n, maSach);
                break;
            case 5:
                printf("Nhap ma sach can cap nhat: ");
                scanf(" %[^\n]s", maSach);
                capNhatSachTheoMa(arr, n, maSach);
                break;
            case 6:
                {
                    int sortChoice;
                    printf("\nMENU SAP XEP\n");
                    printf("1. Tang dan\n");
                    printf("2. Giam dan\n");
                    printf("Lua chon cua ban: ");
                    scanf("%d", &sortChoice);

                    switch (sortChoice) {
                        case 1:
                            sapXepSachTheoGiaTangDan(arr, n);
                            printf("Sach sau khi sap xep tang dan theo gia:\n");
                            break;
                        case 2:
                            sapXepSachTheoGiaGiamDan(arr, n);
                            printf("Sach sau khi sap xep giam dan theo gia:\n");
                            break;
                        default:
                            printf("Lua chon khong hop le!\n");
                            break;
                    }

                    if (sortChoice == 1 || sortChoice == 2) {
                        for (int i = 0; i < n; i++) {
                            hienThiSach(arr[i]);
                            printf("\n");
                        }
                    }
                }
                break;
            case 7:
                printf("Nhap ten sach can tim kiem: ");
                scanf(" %[^\n]s", tenSach);
                timKiemSachTheoTen(arr, n, tenSach);
                break;
            case 8:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
            }	while(choice != 8)
            return 0;
        }