

set(SOURCES app_main.cpp )

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS .
                       REQUIRES lvgl_esp32_drivers lvgl ui shared_task nvs_flash inventory system_status sd_fat
                       EMBED_TXTFILES ${project_dir}/server_certs/ca_cert.pem
                      )

target_compile_definitions(${COMPONENT_LIB} PRIVATE LV_CONF_INCLUDE_SIMPLE=1)



