package main

import (
	"bytes"
	"encoding/binary"
	"github.com/godbus/dbus"
	wpa_supplicant1 "github.com/linuxdeepin/go-dbus-factory/fi.w1.wpa_supplicant1"
	"io"
	"pkg.deepin.io/lib/log"
)

var logger = log.NewLogger("wifi6")

func main() {
	wirelessCap()
}

func wirelessCap() {
	sysBus, err := dbus.SystemBus()
	if err != nil {
		logger.Warningf("system bus %v", err)
		return
	}

	wpaGl := wpa_supplicant1.NewWPASupplicant(sysBus)
	ifcSl, err := wpaGl.Interfaces().Get(0)
	if err != nil {
		logger.Warningf("wpa get ifc failed, err: %v", err)
		return
	}

	if len(ifcSl) == 0 {
		logger.Warning("ifc has not elem")
		return
	}

	ifcPath := ifcSl[0]

	ifc, err := wpa_supplicant1.NewInterface(sysBus, ifcPath)
	if err != nil {
		logger.Warningf("ifc failed, err: %v", err)
		return
	}

	bssSl, err := ifc.Interface().BSSs().Get(0)
	if err != nil {
		logger.Warningf("get bss failed, err: %v", err)
		return
	}

	type element struct {
		id   uint8
		len  uint8
		data []uint8
	}

	for _, bssPath := range bssSl {
		bss, err := wpa_supplicant1.NewBSS(sysBus, bssPath)
		if err != nil {
			logger.Warningf("bss %s failed, err: %v", bssPath, err)
			continue
		}

		ssid, err := bss.SSID().Get(0)
		if err != nil {
			logger.Warningf("%v get ssid failed, err: %v", bssPath, err)
			continue
		}

		logger.Debugf("current ssid %v is %v", ssid, string(ssid))

		if string(ssid) == "" {
			continue
		}

		ies, err := bss.IEs().Get(0)
		if err != nil {
			logger.Warningf("ies failed, err: %v", err)
			continue
		}

		byBuf := bytes.NewBuffer(ies)

		// by
		for {
			var id uint8
			err = binary.Read(byBuf, binary.LittleEndian, &id)
			if err != nil {
				if err == io.EOF {
					break
				}
				logger.Fatalf("id %v", err)
			}
			var dataLen uint8
			err = binary.Read(byBuf, binary.LittleEndian, &dataLen)
			if err != nil {
				logger.Fatalf("length %v", err)
			}
			buf := make([]byte, dataLen)
			err = binary.Read(byBuf, binary.LittleEndian, &buf)
			if err != nil {
				logger.Fatalf("length %v", err)
			}
			if id == 0 {
				logger.Debugf("parse ssid %v is %v", buf, string(buf))
			}
			if id != 255 {
				continue
			}
			extBuf := bytes.NewBuffer(buf)
			var extId uint8
			err = binary.Read(extBuf, binary.LittleEndian, &extId)
			if err != nil {
				logger.Fatalf("ext id %v", err)
			}
			logger.Debugf("%v ext id is %v", string(ssid), extId)
			if extId == 35 {
				logger.Debugf("%v support wifi 6", string(ssid))
			}

		}
	}
}
