(* Desktop module for Augeas
   Author: Raphael Pinson <raphink@gmail.com>


   Reference: Freedesktop.org
      http://standards.freedesktop.org/desktop-entry-spec/desktop-entry-spec-latest.html
*)


module Desktop =
  autoload xfm


let comment  = IniFile.comment "#" "#"

let title = IniFile.title IniFile.record_re

let sep = IniFile.sep "=" "="

let setting = Rx.word

let sto_to_comment = Sep.opt_space . store /[^# \t\n][^#\n]*[^# \t\n]|[^# \t\n]/ 

let entry = [ key setting . sep . sto_to_comment? . (comment|IniFile.eol) ] | comment

(* let entry = Inifile.entry setting sep comment *)

let record  = IniFile.record title entry

let lns    = IniFile.lns record comment

let filter = ( incl "/usr/share/applications" . incl "/usr/share/applications/screensavers" )

let xfm = transform lns filter
