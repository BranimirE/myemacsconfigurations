;; TEST

;; Twit mode :')
(add-to-list 'load-path "~/.emacs-plugins")
(require 'twittering-mode)

;; Cargar tema (Solo emacs 24)
(load-theme 'molokai t)

;; Modo mayor para editar javascript
(add-to-list 'load-path "~/.emacs-plugins/js2-mode")
(autoload 'js2-mode "js2" nil t)
(add-to-list 'auto-mode-alist '("\\.js$" . js2-mode))

;; Usar espacios en vez de tabulaciones
(setq-default indent-tabs-mode nil)

;; Usar 4 espacios como tabs
(setq tab-width 4)

;; Ver los numeros de las lineas
(global-linum-mode t)

;; Cierre automatico de parentesis, brakets, etc.
(setq skeleton-pair t)
(global-set-key "[" 'skeleton-pair-insert-maybe)
(global-set-key "(" 'skeleton-pair-insert-maybe)
(global-set-key "{" 'skeleton-pair-insert-maybe)
(global-set-key "'" 'skeleton-pair-insert-maybe)
(global-set-key "\"" 'skeleton-pair-insert-maybe)

;; Cargar yasnippets
;; (add-to-list 'load-path "~/.emacs-plugins/yasnippet")
;; (require 'yasnippet)
;; (yas-global-mode 1)

;; Para cargar el modo auto-complete mode
(add-to-list 'load-path "~/.emacs.d/")
(require 'auto-complete-config)
(add-to-list 'ac-dictionary-directories "~/.emacs.d/ac-dict/")
(ac-config-default)

;; Mostrar sugerencia de autocompeltacion despues de ingresar un caracter
(setq ac-auto-start 1)

;; Mostrar sugerencias de autocompletacion despues de 0.1 seg.
(setq ac-auto-show-menu 0.1)

;; Resaltar la linea actual
(global-hl-line-mode 1)

;; Poner el fondo en un bonito color #121212
(set-background-color "#121212")

;; Flymake (sin necesidad de crear makefiles)
(require 'flymake)

(defun flymake-cc-init ()
  (let* ((temp-file   (flymake-init-create-temp-buffer-copy
                       'flymake-create-temp-inplace))
         (local-file  (file-relative-name
                       temp-file
                       (file-name-directory buffer-file-name))))
    (list "g++" (list "-fsyntax-only" local-file))))

(push '("\\.cpp$" flymake-cc-init) flymake-allowed-file-name-masks)

(add-hook 'c++-mode-hook
          '(lambda ()
             (flymake-mode t)))
(put 'upcase-region 'disabled nil)

(menu-bar-mode 0)
(tool-bar-mode 0)

(defun run-current-file ()
  "Runs the compilation of the current file.
Assumes it has the same name, but without an extension"
  (interactive)
  (compile (file-name-sans-extension buffer-file-name)))
