MSSV: **23120388**  
Họ và tên: *Phạm Lê Thanh Tú*  
  
MSSV: **23120391**  
Họ và tên: *Đào Bùi Anh Tuấn*  

****PROJECT MUSIC STORE MANAGMENT****
- Source: https://www.codewithc.com/music-store-management-system-c-program-with-mysql-database/#class-dbresponse

*** CÁC DỰ ĐỊNH THỰC HIỆN ***  

1. Khởi tạo các tính năng:  
    a) Tạo đơn hàng mua nhạc  
    b) Tìm kiếm nhạc  
    c) Mặt hàng đã bán  
    d) Mặt hàng trong kho  
    e) Hiển thị tất cả các mục  
    f) Thêm mục mới vào cơ sở dữ liệu  
    g) Chỉnh sửa, xóa, thoát  
2. Viết chương trình theo phương pháp hướng đối tượng  
Dùng các kiến thức đã học để cấu trúc chương trình thành các lớp với các thuộc tính và hành vi phù hợp.  
3. Cải tiến và bổ sung  
Áp dụng nguyên tắc SOLID, các design pattern, nguyên lý dependency injction  
4. Áp dụng kiến trúc phần mềm: Đang thảo luận lựa chọn  
5. Thực hiện đảm bảo chất lượng mã nguồn  
6. Tạo tài liệu mô tả kiến trúc phần mềm  

*** ĐỀ XUẤT CẤU TRÚC CHƯƠNG TRÌNH ***  

**I Đề xuất các nguyên tắt lập trình lập trình ***  

1. Tách lớp rõ ràng theo nhiệm vụ  
2. Sử dụng interface cho các lớp trung gian phụ thuộc  
3. Tạo lớp quản lý đối tượng thay vì xử lý trực tiếp trên lớp đó  
4. Đóng gói dữ liệu, ẩn chi tiết nội bộ  
5. Tcsah rõ logic nghiệp vụ với thao tác dữ liệu  
6. Đặt tên hàm, lớp nhất quán, dễ hiểu  
7. Viết test cho các lớp  
  
**II. Mô tả các lớp**  
1. MusicItem - Lớp cốt lõi  
- Đại diện cho một bảng ghi nhạc trong hệ thống  
- Lớp này chỉ để lưu trữ và cung cấp thông tin, không xử lý logic (Theo nguyên tắc SOLID)  
- Thông tin lưu trữ:  ID bản nhạc, tên bài hát, tên nghệ sĩ, thể loại, giá bán, số lượng tồn kho  
- Các hàm cần thiết: Các hàm get và set  
2. InventoryService - dịch vụ quản lý  
- Lớp đảm nhiệm xử lý liên quan đến các bản ghi nhạc  
- Lớp này không trực tiếp thao tác với cơ sở dữ liệu, mà chỉ gọi các phương thức qua interface trừu tượng (nguyên lý Dependency Inversion)  
- Các hàm cần thiết: Thêm mới bản ghi, chỉnh sửa bản ghi, xóa, tìm kiếm, hiển thị các bản ghi nhạc  
3. OderService - Dịch vụ đơn hàng  
- Chịu trách nhiệm xử lý đơn hàng  
- Không hiển thị dữ liệu hay giao tiếp với người dùng (Nguyên tắc SOLID)  
- Các hàm cần thiết: Kiểm tra số lượng tồm kho, trừ đi số lượng nếu bán, ghi nhận đơn hàng đã bán  
4. Interface  
- Interface định nghĩa các thao tác lưu, cập nhật, xóa, tìm kiếm đối với các bản ghi hay trả về toàn bộ danh sách  
- Lớp này giúp hệ thống không phụ thuộc vào các file, database  
5. MySQLMusicRepository  
- Có chức năng thao tác với database, duy trì tính nhất quán và logic của dữ liệu  
- Các hàm cần thiết: truy vấn SQL để thêm, sửa, xóa, tìm kiếm...  
6. ConsoleUI  
- Lớp giao diện  
- Đây là nơi để xem menu, nhập liệu hay hiển thị kết quả ra màn hình  
- Không xử lí logic, chỉ tương tác với khách hàng  
- Các hàm cần thiết: hiển thị, gọi hiển thị các giao diện khác nhau  
