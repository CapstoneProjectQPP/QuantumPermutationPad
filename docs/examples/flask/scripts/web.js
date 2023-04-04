function multiply(num1, num2) {
  let result = num1 * num2;
  return result;
}

const myHeading = document.querySelector("h1");
const myImage = document.querySelector("img");

myImage.onclick = () => {
  const mySrc = myImage.getAttribute("src");
  if (mySrc === "images/pic.webp") {
    myImage.setAttribute("src", "images/computer.jpg");
  } else {
    myImage.setAttribute("src", "images/pic.webp");
  }
};

myHeading.textContent = "This is a webpage";
multiply(10, 15);

document.querySelector("html").addEventListener("click", () => {
  //alert("Ouch! Stop poking me!");
});

// alert("HI");
