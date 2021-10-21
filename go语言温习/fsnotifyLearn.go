package main

import (
	fs "github.com/fsnotify/fsnotify"
)

func fileWatch() {
	watcher, err := fs.NewWatcher()
}
