import Foundation
import Cocoa

// Hàm tải hình ảnh từ URL
func downloadImage(from url: URL, completion: @escaping (NSImage?) -> Void) {
    let task = URLSession.shared.dataTask(with: url) { data, response, error in
        if let data = data, let image = NSImage(data: data) {
            completion(image)
        } else {
            completion(nil)
        }
    }
    task.resume()
}

// Hàm xử lý hình ảnh (ví dụ: thay đổi kích thước)
func processImage(_ image: NSImage) -> NSImage {
    let newSize = NSSize(width: 100, height: 100)
    let resizedImage = NSImage(size: newSize)
    resizedImage.lockFocus()
    image.draw(in: NSRect(origin: .zero, size: newSize))
    resizedImage.unlockFocus()
    return resizedImage
}

// URL hình ảnh mẫu
let imageUrls = [
    URL(string: "https://example.com/image1.jpg")!,
    URL(string: "https://example.com/image2.jpg")!,
    URL(string: "https://example.com/image3.jpg")!,
]

// Dispatch Group để theo dõi các tác vụ tải về
let dispatchGroup = DispatchGroup()

// Mảng để lưu trữ hình ảnh đã tải
var images: [NSImage] = []

for url in imageUrls {
    dispatchGroup.enter()
    downloadImage(from: url) { image in
        if let image = image {
            let processedImage = processImage(image)
            images.append(processedImage)
        }
        dispatchGroup.leave()
    }
}

// Khi tất cả các tác vụ đã hoàn thành
dispatchGroup.notify(queue: .main) {
    print("Tất cả hình ảnh đã được tải và xử lý!")
    // Xử lý hình ảnh (ví dụ: lưu vào file, hiển thị trên giao diện người dùng)
    // ...
}

// Đợi để chương trình không thoát ngay lập tức
RunLoop.current.run()
