%global build_version %(git describe | sed "s/[0-9]*\.[0-9]*\.[0-9]*-//" | sed "s/-[a-z 0-9]*//")

Name: msgpuck-devel
Version: 1.0.0
Release: %{build_version}
Summary: A MsgPack binary serialization library in a self-contained header
Group: Development/Libraries
License: BSD
URL: https://github.com/rtsisyk/msgpuck
Source0: %{version}.tar.gz
BuildRequires: cmake
Vendor: tarantool.org
%description
A MsgPack binary serialization library in a self-contained header

##################################################################

# Don't fail on ignores .so files
%define _unpackaged_files_terminate_build 0
# Don't create -debuginfo packages
%define debug_package %{nil}

%prep
%setup -c -q msgpuck-%{version}

%build
%cmake . -DCMAKE_INSTALL_LIBDIR='%{_libdir}' -DCMAKE_INSTALL_INCLUDEDIR='%{_includedir}' -DCMAKE_BUILD_TYPE=RelWithDebInfo
make %{?_smp_mflags}

%install
make DESTDIR=%{buildroot} install

%files
"%{_libdir}/libmsgpuck.a"
%dir "%{_includedir}/msgpuck"
"%{_includedir}/msgpuck/msgpuck.h"

%changelog
* Thu Jul 09 2015 Roman Tsisyk <roman@tarantool.org> 1.0.0-1
- Initial version of the RPM spec
