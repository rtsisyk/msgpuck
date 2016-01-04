Name: msgpuck
Version: 1.0.1
Release: 1%{?dist}
Summary: A MsgPack binary serialization library in a self-contained header
Group: Development/Libraries
License: BSD
URL: https://github.com/rtsisyk/msgpuck
Source0: https://github.com/rtsisyk/msgpuck/archive/%{version}/msgpuck-%{version}.tar.gz
BuildRequires: cmake >= 2.8
BuildRequires: doxygen >= 1.8.0

# https://fedoraproject.org/wiki/Packaging:Guidelines#Packaging_Header_Only_Libraries
%package devel
Summary: A MsgPack binary serialization library in a self-contained header.
Provides: msgpuck-static = %{version}-%{release}
Requires: msgpuck%{?_isa} = %{version}-%{release}

%package doc
Summary: Documentation for MsgPuck library
Requires: msgpuck = %{version}-%{release}
BuildArch: noarch

%description
MsgPuck is a simple and efficient MsgPack binary serialization library
in a self-contained header file. MsgPack is an efficient binary
serialization format. It's like JSON. but fast and small.

The library is header only - please install msgpuck-devel for development.

# Nothing to add to -debuginfo package
%global debug_package %{nil}

%description devel
MsgPuck is a simple and efficient MsgPack binary serialization library
in a self-contained header file.

This package provides header file and static library.
Static library is useful when a compiler can't inline some of C functions.

%description doc
MsgPuck is a simple and efficient MsgPack binary serialization library
in a self-contained header file.

This package provides HTML documentation.

%prep
%autosetup -n %{name}-%{version} -p1

%build
%cmake . -DCMAKE_BUILD_TYPE=RelWithDebInfo \
         -DCMAKE_INSTALL_LIBDIR='%{_libdir}' \
         -DCMAKE_INSTALL_INCLUDEDIR='%{_includedir}'
make %{?_smp_mflags}
make doc

%check
make test

%install
%make_install
mkdir -p %{buildroot}%{_pkgdocdir}
mv -f doc/html/msgpuck_8h.html doc/html/index.html
cp -fR doc/html "%{buildroot}%{_pkgdocdir}"
mkdir -p %{buildroot}%{_mandir}/man3
cp -f doc/man/man3/msgpuck.h.3* "%{buildroot}%{_mandir}/man3/"

%files
%doc README.md LICENSE AUTHORS

%files devel
"%{_libdir}/libmsgpuck.a"
"%{_includedir}/msgpuck.h"
"%{_mandir}/man3/msgpuck.h.3*"

%files doc
"%{_pkgdocdir}/html"

%changelog
* Sun Jul 03 2016 Roman Tsisyk <roman@tsisyk.com> 1.0.1-1
- A new version with the ful support of ARMv6 and AARCH64 systems
- Fixes to match Fedora packaging policies
* Thu Jul 09 2015 Roman Tsisyk <roman@tsisyk.com> 1.0.0-1
- Initial version of the RPM spec
