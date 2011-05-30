# Inherit AOSP device configuration for Kyros 7015.
$(call inherit-product, device/coby/kyros7015/full_kyros7015.mk)

# Inherit some common cyanogenmod stuff.
$(call inherit-product, vendor/cyanogen/products/common_full.mk)

# Include GSM stuff
$(call inherit-product, vendor/cyanogen/products/gsm.mk)

#
# Setup device specific product configuration.
#
PRODUCT_NAME := cyanogen_kyros7015
PRODUCT_BRAND := coby
PRODUCT_DEVICE := kyros7015
PRODUCT_MODEL := Kyros 7015
PRODUCT_MANUFACTURER := COBY
PRODUCT_BUILD_PROP_OVERRIDES += PRODUCT_NAME=kyros7015 BUILD_ID=GRJ22 BUILD_DISPLAY_ID=GRJ22 BUILD_FINGERPRINT=google/soju/crespo:2.3.4/GRJ22/121341:user/release-keys PRIVATE_BUILD_DESC="soju-user 2.3.4 GRJ22 121341 release-keys" BUILD_NUMBER=121341

# Extra Kyros 7015 overlay
PRODUCT_PACKAGE_OVERLAYS += vendor/coby/kyros7015/overlay

#
# Set ro.modversion
#
ifdef CYANOGEN_NIGHTLY
    PRODUCT_PROPERTY_OVERRIDES += \
        ro.modversion=CyanogenMod-7-$(shell date +%m%d%Y)-NIGHTLY-KYROS7015
else
    ifdef CYANOGEN_RELEASE
        PRODUCT_PROPERTY_OVERRIDES += \
            ro.modversion=CyanogenMod-7.1.0-RC0-KYROS7015
    else
        PRODUCT_PROPERTY_OVERRIDES += \
            ro.modversion=CyanogenMod-7.1.0-RC0-KYROS7015-KANG
    endif
endif

#
# Copy Kyros 7015 specific prebuilt files
#
PRODUCT_COPY_FILES +=  \
    vendor/cyanogen/prebuilt/mdpi/media/bootanimation.zip:system/media/bootanimation.zip
