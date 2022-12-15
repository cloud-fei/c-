Name:          project1
Version:       VERSION
Release:       RELEASE
Summary:       It is a fs expired server for Unix-like systems
License:       GPLv2 with exceptions
Source0:       %{name}-%{version}.tar.gz
Source1:       %{name}.conf
Source2:       %{name}.service
BuildRequires: systemd make gcc
#Requires:      
%description
project1, is a fs expired for Unix-like systems, including Linux.
It is licensed under the GNU General Public License.

%prep
rm -rf %_builddir/%{name}-%{version}
mkdir -p %_builddir/%{name}-%{version}
tar -xvf %_sourcedir/%{name}-%{version}.tar.gz -C %_builddir/
#tar -xvf %_sourcedir/%{name}-%{version}.tar.gz -C %_builddir/%{name}-%{version} --strip-components 1
cd %_builddir/%{name}-%{version}

%build
mkdir -p %_builddir/%{name}-%{version}/build
rm -rf %_builddir/%{name}-%{version}/build/*
cd %_builddir/%{name}-%{version}/build
cmake ..
make %{?_smp_mflags}

%install
install -Dm755 %_builddir/%{name}-%{version}/build/%{name} %{buildroot}%{_bindir}/%{name}
install -Dm600 %{SOURCE1} %{buildroot}%{_sysconfdir}/%{name}.conf
mkdir -p %{buildroot}%{_unitdir}
install -m644 %{SOURCE2} %{buildroot}%{_unitdir}/%{name}.service

%post
%systemd_post %{SOURCE2}
%preun
%systemd_preun %{SOURCE2}
%postun
%systemd_postun_with_restart %{SOURCE2}

%files
%config(noreplace) /etc/%{name}.conf
%{_unitdir}/*
#%{generator_dir}/*
%{_bindir}/%{name}
%{_sysconfdir}/%{name}.conf

%changelog
* Tue Dec 12 2022 xxx <xxx> - 1.0.0.0
- first Release