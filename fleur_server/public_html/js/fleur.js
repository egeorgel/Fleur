/* Websockets */
var socket = new WebSocket("wss://fleur.how:2102", 'base64');
socket.onerror = function() {
	show_error_modal();
}
socket.onclose = function() {
	show_error_modal();
}
var sent_queries = []; // LIFO Buffer to store all the queries
socket.onmessage = function(evt) {
	var query = sent_queries.shift();
	if (query === "undefined")
		query = "Next part";
	var response = b64DecodeUnicode(evt.data);
	add_history(query, response); // Message is received in base64 so we need to decode it
}
function b64DecodeUnicode(str) {
    return decodeURIComponent(Array.prototype.map.call(atob(str), function(c) {
        return '%' + ('00' + c.charCodeAt(0).toString(16)).slice(-2);
    }).join(''));
}
socket.query = function(query) {
	var queries = query.split("\n");
	for (var i=0;i<queries.length-1;i++)
		sent_queries.push(queries[i]);
	socket.send(btoa(query)); // Base 64 preprocessor before socket.send
}


/* App */
$(document).ready(init);
function init() {
	var image = document.getElementById('background');
	image.onload = load; // When the background image is loaded we start the whole app
	image.src = 'img/bg.jpg?denis';
	image.crossOrigin = 'anonymous';
}

function load() {
	/* Initial Animation */
	$("#wrapper").addClass('landed');
	
	/* Rainyday window resize observer */
	/*function resize_canvas() {
		var canvas = $("canvas");
		var img = $("#background");
		canvas.width(img.width());
		canvas.height(img.height());
	}
	resize_canvas();
	window.onresize = resize_canvas;
	*/	
	/* RainyDay */
	/*var engine = new RainyDay({
	        image: this
	});
	engine.rain([ [0, 2, 20], [3, 3, 1] ], 100);
	*/
	/* Textarea keypress observer, handles ENTER and SHIFT+ENTER */
	function handleEnter(evt) {
	    if (evt.keyCode == 13 && !evt.shiftKey) {
		    var query = $("textarea").val().trim();
		    if (query != "") {
		        socket.query(query+"\n");
		        $("textarea").val('');
		        $("hr").css('top', '35px');
		    }
	        evt.preventDefault();
	    }
	}
	$("textarea").keydown(handleEnter).keypress(handleEnter);
	
	/* Textarea bottom line handler */
	$("textarea").on('input',function(e) {
		var text = $(this).val();   
		var lines = text.split(/\r|\r\n|\n/);
		$("hr").css('top', (5+30*lines.length)+'px');
	});
	
	/* Modal Reload Button & Action */
	$("#reload").click(function(){window.location.reload();});
	$('#error-modal').on('hide.bs.modal', function(){window.location.reload();});
	
	/* Sidebar Buttons */
	$("#action-documentation").click(toggle_documentation);
	$("#action-history").click(toggle_history);
}

/* Helpers */
function nl2br (str, is_xhtml) {
    var breakTag = (is_xhtml || typeof is_xhtml === 'undefined') ? '<br />' : '<br>';
    return (str + '').replace(/([^>\r\n]?)(\r\n|\n\r|\r|\n)/g, '$1' + breakTag + '$2');
}
function escapeHtml (string) {
  var entityMap = {
	  '&': '&amp;',
	  '<': '&lt;',
	  '>': '&gt;',
	  '"': '&quot;',
	  "'": '&#39;',
	  '/': '&#x2F;',
	  '`': '&#x60;',
	  '=': '&#x3D;'
	};
  return String(string).replace(/[&<>"'`=\/]/g, function (s) {
    return entityMap[s];
  });
}
function show_error_modal() {
	$("#error-modal").modal('show');
}
function add_history(title, message) {
	toggle_history();
	$("#history").prepend('<li><span class="small">'+nl2br(title)+'</span><br /><span class="big"><pre>'+escapeHtml(message)+'</pre></span></li>');
}
function toggle_history() {
	$("#history, #action-documentation").show();
	$("#documentation, #action-history").hide();
}
function toggle_documentation() {
	$("#history, #action-documentation").hide();
	$("#documentation, #action-history").show();
}
