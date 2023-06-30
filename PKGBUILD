pkgname=OpenBattery
pkgver=2.6
pkgrel=1
pkgdesc="Terminal-based battery monitor"
arch=('x86_64')
url="https://github.com/ToujoursTitou2/OpenBattery"
license=('GPL3')
depends=() 
maintainer=("Titou");
source=("OpenBattery-v2.6.tar.gz")
sha256sums=('65fae47a97959c3ccdb7175e5b5ada653116298ccb032a8aae8e7eec48880413')

package(){
    cd "$srcdir"
    make DESTDIR="$pkgdir"
}
