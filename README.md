# Flappy Bird 

## Game Structure

Sử dụng C++ và thư viện SDL2
( scr: chứa file .cpp & include: chứa file .h)

### Các đối tượng có trong game
* bird: bay lên hoặc bay xuống.
* threat: là chướng ngại vật bird phải vượt qua, di chuyển liên tục về bên trái.
* background: cũng di chuyển liên tục về bên trái, có mặt đất.
* các đối tượng khác: sound, text...

### Cách chơi
* bắt đầu game sẽ có màn hình start có 2 lựa chọn "Play" và "Exit":
    * nhấn "Play" thì bắt đầu chơi.
    * nhấn "Exit" (hoặc phím ESC) thì sẽ thoát game.
* sau khi nhấn "Play" sẽ hiện ra màn hình tap_play, nhấn chuột vào màn hình để chơi.
* sau đó sẽ xuất hiện màn hình chơi chính:
    * nhấn chuột trái hoặc phím SPACE để điều khiển con bird.
    * mỗi lần bird vượt qua 1 threat thì điểm sẽ cộng 1.
    * khi bird va chạm với threat, với biên của background, với mặt đất thì sẽ chết.
    * trong khi chơi nhấn phím "**s**" nếu muốn **pause** game.
* khi bird chết sẽ hiện ra màn hình gameover:
    * có 2 lựa chọn cho người chơi "Play" và "Exit": nhấn "Play" để chơi lại còn nhấn "Exit" để thoát khỏi game.
    * trên màn hình còn có hiện điểm của người chơi: "Score" là điểm lần vừa chơi và "Best" là điểm cao nhất trong các lần chơi trước đó( khi tắt game "Best" không được lưu).
    
### Chức năng của các file trong chương trình
* LTexture: tạo texture từ ảnh nhờ đường dẫn truyền vào, tạo texture từ chữ nhờ string truyền vào và render texture. Ngoài ra còn có hàm check 1 điểm có tọa độ (x, y) có nằm trong 1 rect hay không; hàm lấy height, lấy width của texture;...
* Bird: quản lí bird bằng các hàm xử lí sự kiện truyền vào; di chuyển;...
* Threat: tạo chướng ngại vật trong game bằng các hàm.
* Text: xử lí việc đặt màu chữ; load chữ, màu chữ, font chữ; vẽ chữ lên màn hình game;...
* Menu: tạo các màn hình khi bắt đầu game và khi kết thúc game.
* Game: tạo các hàm xử lí việc load các thư viện trong SDL; load ảnh; load âm thanh; xây dựng chương trình chơi chính cho game;...
* main: chạy toàn bộ game nhờ các hàm đã viết.

