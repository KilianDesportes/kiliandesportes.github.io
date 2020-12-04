function affichManipul(btnID,divID,msg) {
	        if(document.getElementById(divID).style.display == "none") {
	            document.getElementById(divID).style.display = "block";
	            document.getElementById(btnID).innerHTML = "Hide " + msg;
	        } else {
	            document.getElementById(divID).style.display = "none";
	            document.getElementById(btnID).innerHTML = "Show " + msg;
	        }
	    }