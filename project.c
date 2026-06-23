ĐÁNH GIÁ CHẤT LƯỢNG KỸ NĂNG
LẬP TRÌNH PYTHON – ĐỀ THI CUỐI MÔN
[Đề bài số 007]
THỜI GIAN: 90 phút
*******************
Yêu cầu:
Tạo project folder theo hướng dẫn sau:
Tạo folder [Mã Lớp]_[Họ Tên]_[Mã Đề] chứa toàn bộ file mã nguồn
Ví dụ: HN_KS25_CNTT1_NguyenVanA_007
Sau khi hoàn thành project, đẩy code lên github và nộp link cho người phụ trách
Công nghệ & công cụ sử dụng: Python, Visual Studio Code
Thực hành
1. Bối cảnh
Một thư viện đang quản lý thông tin mượn sách và tiền phạt bằng Excel thủ công nên gặp nhiều vấn đề:
Dễ nhập trùng mã phiếu mượn
Khó kiểm soát dữ liệu sai như số ngày mượn, số ngày trễ hạn
Khó tìm kiếm người mượn hoặc sách đã mượn
Tính tiền phạt thủ công dễ sai
Khó thống kê số lượng phiếu mượn theo từng mức phạt
Vì vậy cần xây dựng hệ thống CLI Python quản lý thư viện và tính tiền phạt tự động.
2. Mục tiêu hệ thống
Xây dựng chương trình Python cho phép:
Quản lý danh sách phiếu mượn sách bằng OOP
Thêm, hiển thị, cập nhật, xóa phiếu mượn
Tìm kiếm phiếu mượn
Tính tiền phạt tự động
Phân loại mức phạt tự động
Thống kê số lượng phiếu mượn theo từng mức phạt
3. Yêu cầu thiết kế OOP
3.1. Class LibraryBorrow
Class LibraryBorrow dùng để mô tả thông tin mượn sách của một bạn đọc.
Thuộc tính bắt buộc:
id — Mã phiếu mượn
reader_name — Họ tên bạn đọc
book_name — Tên sách
borrow_days — Số ngày đã mượn
late_days — Số ngày trễ hạn
fine_per_day — Tiền phạt mỗi ngày trễ
total_fine — Tổng tiền phạt
fine_type — Phân loại mức phạt
Phương thức:
calculate_fine()
classify_fine()
Yêu cầu:
calculate_fine() dùng để tính và cập nhật total_fine.
classify_fine() dùng để phân loại và cập nhật fine_type.
Không nhập total_fine và fine_type từ bàn phím.
total_fine và fine_type phải được cập nhật thông qua method của class LibraryBorrow.
3.2. Class LibraryBorrowManager
Class LibraryBorrowManager dùng để quản lý danh sách phiếu mượn sách.
class LibraryBorrowManager:
    def __init__(self):
        self.borrow_records = []
Phương thức:
add_borrow_record()
show_all()
update_borrow_record()
delete_borrow_record()
search_borrow_record()
4. Công thức xử lý
4.1. Tính tổng tiền phạt
Tổng tiền phạt = Số ngày trễ hạn × Tiền phạt mỗi ngày trễ
Lưu ý: Nếu số ngày trễ hạn bằng 0 thì tổng tiền phạt là 0.
4.2. Phân loại mức phạt
Tổng tiền phạt
Phân loại mức phạt
Bằng 0
Không phạt
Trên 0 đến dưới 50,000
Nhẹ
Từ 50,000 đến dưới 200,000
Trung bình
Từ 200,000 trở lên
Nặng

5. Menu chương trình
================ MENU ================
1. Hiển thị danh sách phiếu mượn
2. Thêm phiếu mượn mới
3. Cập nhật phiếu mượn
4. Xóa phiếu mượn
5. Tìm kiếm phiếu mượn
6. Thoát
=====================================
Nhập lựa chọn của bạn:
6. Yêu cầu chi tiết chức năng
Chức năng 1. Hiển thị danh sách phiếu mượn  (15 điểm)
Hiển thị danh sách phiếu mượn dạng bảng gồm các cột:
Mã phiếu mượn
Họ tên bạn đọc
Tên sách
Số ngày đã mượn
Số ngày trễ hạn
Tiền phạt mỗi ngày
Tổng tiền phạt
Phân loại mức phạt
Nếu danh sách rỗng, hiển thị thông báo: Danh sách phiếu mượn đang rỗng!
Chức năng 2. Thêm phiếu mượn mới  (20 điểm)
Người dùng nhập:
Mã phiếu mượn
Họ tên bạn đọc
Tên sách
Số ngày đã mượn
Số ngày trễ hạn
Tiền phạt mỗi ngày trễ
Ràng buộc
Mã phiếu mượn không được rỗng
Mã phiếu mượn không được trùng
Họ tên bạn đọc không được rỗng
Tên sách không được rỗng
Số ngày đã mượn phải là số nguyên từ 1 đến 365
Số ngày trễ hạn phải là số nguyên từ 0 đến 365
Số ngày trễ hạn không được lớn hơn số ngày đã mượn
Tiền phạt mỗi ngày trễ phải lớn hơn hoặc bằng 0
Sau khi thêm thành công, chương trình phải tự động:
Tính tổng tiền phạt
Phân loại mức phạt
Thêm phiếu mượn vào danh sách
Thông báo: Thêm phiếu mượn thành công!
Chức năng 3. Cập nhật phiếu mượn  (20 điểm)
Người dùng nhập mã phiếu mượn cần cập nhật.
Nếu mã phiếu mượn không tồn tại, hiển thị: Không tìm thấy phiếu mượn cần cập nhật!
Nếu tồn tại, cho phép cập nhật:
Số ngày đã mượn
Số ngày trễ hạn
Tiền phạt mỗi ngày trễ
Sau khi cập nhật thành công, chương trình phải:
Tính lại tổng tiền phạt
Cập nhật lại phân loại mức phạt
Thông báo: Cập nhật phiếu mượn thành công!
Chức năng 4. Xóa phiếu mượn  (15 điểm)
Người dùng nhập mã phiếu mượn cần xóa.
Nếu mã phiếu mượn không tồn tại, hiển thị: Không tìm thấy phiếu mượn cần xóa!
Nếu tồn tại, hỏi xác nhận: Bạn có chắc muốn xóa phiếu mượn này không? (Y/N):
Nếu nhập Y hoặc y → xóa phiếu mượn
Nếu nhập N hoặc n → hủy thao tác
Các lựa chọn khác → thông báo lựa chọn không hợp lệ
Thông báo khi xóa thành công: Xóa phiếu mượn thành công!
Thông báo khi hủy: Đã hủy thao tác xóa!
Chức năng 5. Tìm kiếm phiếu mượn  (15 điểm)
Chương trình hỗ trợ tìm kiếm theo tên bạn đọc hoặc tên sách.
Yêu cầu:
Tìm kiếm gần đúng
Không phân biệt chữ hoa, chữ thường
Có thể tìm theo một phần tên bạn đọc hoặc một phần tên sách
Ví dụ:
Nhập từ khóa tìm kiếm: python
Có thể tìm thấy:
Nguyễn Văn An - Lập trình Python cơ bản
Trần Thị Bình - Python OOP
Nếu không tìm thấy, hiển thị: Không tìm thấy phiếu mượn phù hợp!
Chức năng 6. Thoát chương trình  (5 điểm)
Khi người dùng chọn chức năng thoát, chương trình kết thúc an toàn và in lời chào:
Cảm ơn bạn đã sử dụng hệ thống quản lý thư viện!
7. Yêu cầu kỹ thuật bắt buộc
7.1. OOP bắt buộc
Phải có class LibraryBorrow
Phải có class LibraryBorrowManager
Không dùng dict làm cấu trúc chính để quản lý phiếu mượn
Danh sách phiếu mượn phải được quản lý thông qua list object
7.2. Encapsulation
Không tính tiền phạt từ bên ngoài class LibraryBorrow
total_fine phải được cập nhật thông qua method calculate_fine()
fine_type phải được cập nhật thông qua method classify_fine()
Không nhập trực tiếp total_fine và fine_type từ bàn phím
7.3. Clean Code
Mỗi function chỉ làm một nhiệm vụ
Không viết toàn bộ logic trong main
Có hàm riêng để nhập số hợp lệ
Có hàm riêng để hiển thị menu
Tên biến, tên hàm rõ ràng, dễ hiểu
Code có khả năng đọc và bảo trì
7.4. Validate dữ liệu
Chương trình cần kiểm tra:
Không trùng mã phiếu mượn
Không để trống mã phiếu mượn
Không để trống họ tên bạn đọc
Không để trống tên sách
Số ngày đã mượn phải là số nguyên hợp lệ
Số ngày trễ hạn phải là số nguyên hợp lệ
Số ngày đã mượn nằm trong khoảng từ 1 đến 365
Số ngày trễ hạn nằm trong khoảng từ 0 đến 365
Số ngày trễ hạn không được lớn hơn số ngày đã mượn
Tiền phạt mỗi ngày trễ không được âm
7.5. Xử lý lỗi
Chương trình cần xử lý các trường hợp:
Danh sách rỗng
Không tìm thấy phiếu mượn
Nhập sai kiểu dữ liệu
Nhập sai lựa chọn menu
Người dùng không xác nhận xóa
Số ngày trễ hạn lớn hơn số ngày đã mượn
8. Thang điểm
Nội dung
Điểm
Hiển thị danh sách phiếu mượn
15
Thêm phiếu mượn
20
Cập nhật phiếu mượn
20
Xóa phiếu mượn
15
Tìm kiếm phiếu mượn
15
Clean code + validate
10
Thoát chương trình + UX
5
Tổng
100

Lưu ý: Chỉ tính điểm khi chức năng chương trình thực hiện đúng theo yêu cầu nghiệp vụ được giao

