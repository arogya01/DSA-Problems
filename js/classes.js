class Rectangle {
  constructor(height, width) {
    this.width = width;
    this.height = height;
  }

  getHeight() {
    console.log("the height and widht is ", this.height, this.width);
  }
}

const rec = new Rectangle(10, 20);
rec.getHeight();
