Name: msgpuck
Version: 1.0.1
Release: 1%{?dist}
Summary: MsgPack binary serialization library in a self-contained header
Group: Development/Libraries
License: BSD
URL: https://github.com/rtsisyk/msgpuck
Source0: https://github.com/rtsisyk/msgpuck/archive/%{version}/msgpuck-%{version}.tar.gz
BuildRequires: cmake >= 2.8
BuildRequires: doxygen >= 1.7.0

# https://fedoraproject.org/wiki/Packaging:Guidelines#Packaging_Header_Only_Libraries
# Nothing to add to -debuginfo package - this library is header-only
%global debug_package %{nil}

%package devel
Summary: MsgPack serialization library in a self-contained header file
Provides: msgpuck-static = %{version}-%{release}
Requires: msgpuck%{?_isa} = %{version}-%{release}

%description
MsgPack is a binary-based efficient object serialization library.
It enables to exchange structured objects between many languages like JSON.
But unlike JSON, it is very fast and small.

msgpuck is very lightweight header-only library designed to be inlined to
your application by the C/C++ compiler. The library is fully documented and
covered by unit tests.

%description devel
MsgPack is a binary-based efficient object serialization library.
It enables to exchange structured objects between many languages like JSON.
But unlike JSON, it is very fast and small.

msgpuck is very lightweight header-only library designed to be inlined to
your application by the C/C++ compiler. The library is fully documented and
covered by unit tests.

This package provides a self-contained header file and a static library.
The static library contains generated code for inlined functions and
globals tables needed by the some library functions.

%prep
%setup -q -n %{name}-%{version}

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
mkdir -p %{buildroot}%{_mandir}/man3
cp -f doc/man/man3/msgpuck.h.3* "%{buildroot}%{_mandir}/man3/"

%files devel
%{_libdir}/libmsgpuck.a
%{_includedir}/msgpuck.h
%{_mandir}/man3/msgpuck.h.3*
%doc README.md
%{!?_licensedir:%global license %doc}
%license LICENSE AUTHORS

%changelog
* Sun Jul 10 2016 Roman Tsisyk <roman@tsisyk.com> 1.0.1-1
- Changes according to Fedora review #1295217
- Fix SIGBUS on processesor without HW support for unaligned access
* Thu Jul 09 2015 Roman Tsisyk <roman@tsisyk.com> 1.0.0-1
- Initial version of the RPM spec
