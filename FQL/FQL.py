import sublime
import sublime_plugin

class FqlDisplayResultsCommand(sublime_plugin.TextCommand):
  def run(self, edit, selectionText):
    self.view.insert(edit, 0, selectionText)

class FqlEchoCommand(sublime_plugin.WindowCommand):
  def run(self):
    window = self.window
    view = window.active_view()
    sel = view.sel()
    selectionText = view.substr(sel[0])

    if selectionText:
      # TODO: Check if correct FQL command
      new_window = window.new_file()
      new_window.run_command('fql_display_results', {'selectionText': selectionText})
    else:
      sublime.message_dialog("Select a FQL command first")