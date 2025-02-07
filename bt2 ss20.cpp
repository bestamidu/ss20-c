#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100


typedef struct {
    char maSP[10];
    char tenSP[50];
    float giaNhap;
    float giaBan;
    int soLuong;
} SanPham;

void nhapSanPham(SanPham *sp) {
    printf("Nhap ma san pham: ");
    scanf(" %[^\n]s", sp->maSP);
    printf("Nhap ten san pham: ");
    scanf(" %[^\n]s", sp->tenSP);
    printf("Nhap gia nhap: ");
    scanf("%f", &sp->giaNhap);
    printf("Nhap gia ban: ");
    scanf("%f", &sp->giaBan);
    printf("Nhap so luong: ");
    scanf("%d", &sp->soLuong);
}


void hienThiSanPham(SanPham sp) {
    printf("Ma san pham: %s\n", sp.maSP);
    printf("Ten san pham: %s\n", sp.tenSP);
    printf("Gia nhap: %.2f\n", sp.giaNhap);
    printf("Gia ban: %.2f\n", sp.giaBan);
    printf("So luong: %d\n", sp.soLuong);
}


int timKiemSanPhamTheoMa(SanPham *arr, int n, char *maSP) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].maSP, maSP) == 0) {
            return i;
        }
    }
    return -1;
}


void sapXepSanPhamTheoGiaTangDan(SanPham *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].giaBan > arr[j + 1].giaBan) {
                SanPham temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sapXepSanPhamTheoGiaGiamDan(SanPham *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].giaBan < arr[j + 1].giaBan) {
                SanPham temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void timKiemSanPhamTheoTen(SanPham *arr, int n, char *tenSP) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(arr[i].tenSP, tenSP) != NULL) {
            hienThiSanPham(arr[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay san pham co ten %s.\n", tenSP);
    }
}

int main() {
    SanPham arr[MAX_PRODUCTS];
    int n = 0, choice, soLuongBan;
    char maSP[10], tenSP[50];
    float doanhThu = 0;

    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin san pham.\n");
        printf("2. Hien thi danh sach san pham.\n");
        printf("3. Nhap san pham.\n");
        printf("4. Cap nhat thong tin san pham.\n");
        printf("5. Sap xep san pham theo gia(tang/giam).\n");
        printf("6. Tim kiem san pham.\n");
        printf("7. Ban san pham (co the nhap so luong can ban)\n");
        printf("8. Doanh thu hien tai\n");
        printf("9. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap so luong san pham: ");
                scanf("%d", &n);
                printf("Nhap thong tin san pham:\n");
                for (int i = 0; i < n; i++) {
                    nhapSanPham(&arr[i]);
                    doanhThu -= arr[i].giaNhap * arr[i].soLuong;
                }
                break;
            case 2:
                printf("Danh sach san pham:\n");
                for (int i = 0; i < n; i++) {
                    hienThiSanPham(arr[i]);
                    printf("\n");
                }
                break;
            case 3:
                {
                    SanPham sp;
                    nhapSanPham(&sp);
                    int index = timKiemSanPhamTheoMa(arr, n, sp.maSP);
                    if (index != -1) {
                        arr[index].soLuong += sp.soLuong;
                        printf("Da cap nhat so luong cho san pham co ma %s.\n", sp.maSP);
                    } else {
                        arr[n] = sp;
                        n++;
                        printf("Da them san pham moi.\n");
                    }
                    doanhThu -= sp.giaNhap * sp.soLuong;
                }
                break;
            case 4:
                printf("Nhap ma san pham can cap nhat: ");
                scanf(" %[^\n]s", maSP);
                int index = timKiemSanPhamTheoMa(arr, n, maSP);
                if (index != -1) {
                    printf("Nhap thong tin san pham moi:\n");
                    nhapSanPham(&arr[index]);
                    printf("Da cap nhat thong tin san pham co ma %s.\n", maSP);
                } else {
                    printf("Khong tim thay san pham co ma %s.\n", maSP);
                }
                break;
            case 5:
                {
                    int sortChoice;
                    printf("\nMENU SAP XEP\n");
                    printf("1. Tang dan\n");
                    printf("2. Giam dan\n");
                    printf("Lua chon cua ban: ");
                    scanf("%d", &sortChoice);

                    switch (sortChoice) {
                        case 1:
                            sapXepSanPhamTheoGiaTangDan(arr, n);
                            printf("San pham sau khi sap xep tang dan theo gia:\n");
                            break;
                        case 2:
                            sapXepSanPhamTheoGiaGiamDan(arr, n);
                            printf("San pham sau khi sap xep giam dan theo gia:\n");
                            break;
                        default:
                            printf("Lua chon khong hop le!\n");
                            break;
                    }

                    if (sortChoice == 1 || sortChoice == 2) {
                        for (int i = 0; i < n; i++) {
                            hienThiSanPham(arr[i]);
                            printf("\n");
                        }
                    }
                }
                break;
            case 6:
                printf("Nhap ten san pham can tim kiem: ");
                scanf(" %[^\n]s", tenSP);
                timKiemSanPhamTheoTen(arr, n, tenSP);
                break;
            case 7:
                printf("Nhap ma san pham can ban: ");
                scanf(" %[^\n]s", maSP);
                int indexBan = timKiemSanPhamTheoMa(arr, n, maSP);
                if (indexBan != -1) {
                    printf("Nhap so luong can ban: ");
                    scanf("%d", &soLuongBan);
                    if (soLuongBan > arr[indexBan].soLuong) {
                        printf("Khong con du hang.\n");
                    } else if (arr[indexBan].soLuong == 0) {
                        printf("Het hang.\n");
                    } else {
                        arr[index