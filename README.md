# BSDSay - Talking BSD Daemon

Inspired by cowsay but instead of showing the cow it shows the BSD Daemon.

## Installation

You can compile the bsdsay.c file manually or either run the Makefile provided in the repo.
For the Makefile you will have to make sure gcc is installed on your system.

```
xz3k@gentoo ffind $ make bsdsay
xz3k@gentoo ffind $ chmod +x bsdsay
xz3k@gentoo ffind $ doas cp bsdsay /bin
```

**Note** : You may edit the CFLAFS or the CC in the Makefile.
