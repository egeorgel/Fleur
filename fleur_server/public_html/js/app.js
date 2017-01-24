$(document).ready(function() {
  $('.modal-background').click(function() {
    $('html').removeClass('is-clipped');
    $(this).parent().removeClass('is-active');
  });

  // trigger extension
  ace.require("ace/ext/language_tools");
  var editor = ace.edit("editor");
  editor.session.setMode("ace/mode/html");
  editor.setTheme("ace/theme/tomorrow");
  // enable autocompletion and snippets
  editor.setOptions({
      enableBasicAutocompletion: true,
      enableSnippets: false,
      enableLiveAutocompletion: true,
      maxLines: 1,
      showGutter: false,
      autoScrollEditorIntoView: false,
      mode: "ace/mode/fql",
      theme: "ace/theme/xcode",
      highlightActiveLine: false
  });
  editor.commands.removeCommands(["gotoline", "find"]) 
  editor.commands.addCommand({
  name: "execute",
  bindKey: "Enter|Shift-Enter",
  exec: function(editor) {
      $('html').addClass('is-clipped');
      $('#modal').addClass('is-active');
    }
  });
  editor.renderer.setScrollMargin(10, 10);
  editor.focus();
});
function run() {
                var image = document.getElementById('background');
                image.onload = function() {
                    var engine = new RainyDay({
                        image: this
                    });
					engine.rain([ [0, 2, 20], [3, 3, 1] ], 100);
				};
                image.crossOrigin = 'anonymous';
                image.src = 'img/fleur.jpg';
            }
