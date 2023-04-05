var vector_radio = document.getElementById('vector_selected');
var file_radio =  document.getElementById('file_selected');


if(vector_radio.checked) {
    document.getElementById('testing').innerHTML = "What up";
    document.getElementById("vector_options").style.display = "block";  
    document.getElementById("file_options").style.display = "none";
} else if(file_radio.checked) {
    document.getElementById('testing').innerHTML = "Guy";
    document.getElementById("vector_options").style.block = "none";
    document.getElementById("file_options").style.block = "block";
}
