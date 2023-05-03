
################deb-пакет########################
#Указываем на то, что формируется deb-пакет  - с расширением  .deb:
SET(CPACK_GENERATOR "DEB")
#Формируется архив с исходными кодами для deb-пакета (это не обязательно) - с расширением .dsc:
SET(CPACK_SOURCE_GENERATOR "DEB")
#Наименование разработчика:
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "RKB GLOBUS")
#Наименование разработчика:
SET(CPACK_PACKAGE_CONTACT "niia_ru")
#Необходимо включить создание deb-пакета, а все остальное - надо обязательно отключить ,чтобы не собирались:
SET(CPACK_BINARY_DEB ON)
SET(CPACK_BINARY_STGZ OFF)
SET(CPACK_BINARY_TGZ OFF)
SET(CPACK_BINARY_TZ OFF)
SET(CPACK_BINARY_TBZ2 OFF)
#Определим версию
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
#имя deb-пакета - то как он будет называться
SET(CPACK_PACKAGE_NAME "server331")
#название целевой операционной системы (AstraLinux-SE_1_3)
SET(CPACK_SYSTEM_NAME "AstraLinux-x86_64")
#Указание того, кто создает deb-пакет
SET(CPACK_PACKAGE_VENDOR "RKB GLOBUS")
SET(CPACK_INSTALL_PREFIX "/user_no_gui")

SET(CPACK_TOPLEVEL_TAG "AstraLinux-x86_64")
#Включение исполняемых сценариев сопровождающего, автоматически запускаемых до или после установки пакета:
#   preinst - выполняется перед тем, как пакет будет распакован из deb-пакета.
#для многих пакетов при их обновлении задаётся остановка связанных с ними служб до тех пор, пока обновление или установка не закончится
set( CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/package/preinst;${CMAKE_CURRENT_SOURCE_DIR}/package/postinst;${CMAKE_CURRENT_SOURCE_DIR}/package/postrm;" )
#   postinst - для завершения всей необходимой настройки пакета после его распаковки из deb-пакета.
#у пользователя запрашиваются различные параметры и/или пользователь предупреждается,
#что если он примет предлагаемые по умолчанию значения, позже он должен не забыть перенастроить этот пакет в соответствии со своей ситуацией.
#Затем выполняются команды, необходимые для запуска или перезапуска служб после установки или обновления пакета
#   postrm - служит для изменения ссылок или других файлов, связанных с p215, и/или удаления файлов, созданных пакетом.
#   prerm  - служит для остановки всех связанных с пакетом служб. Он выполняется перед удалением файлов данного пакета.
# система управления пакетами использует зависимости от следующих библиотек:

#Сборка пакетов для исполняемых и исходных файлов.
INCLUDE(CPack)


message("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&Add DEB Tools FOR user_no_gui")
set(mod755   OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
set(mod4755  OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE SETUID)
set(mod744   OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ  WORLD_READ)
set(mod666   OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ WORLD_WRITE)
set(mod644   OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)


install(FILES ${CMAKE_SOURCE_DIR}/bin/user_no_gui          PERMISSIONS  ${mod4755}    DESTINATION ../opt/user_no_gui/)
install(FILES ${CMAKE_SOURCE_DIR}/package/profile          PERMISSIONS  ${mod4755}    DESTINATION ../etc/)





