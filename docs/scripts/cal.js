let myButton = document.querySelector("button");
let myHeading = document.querySelector("h1");
setUserName();

myButton.onclick = () => {
  setUserName();
};

function setUserName() {
  const myName = prompt("Please enter your name.");
  localStorage.setItem("name", myName);
  myHeading.textContent = `Your name is ${myName}`;
}
