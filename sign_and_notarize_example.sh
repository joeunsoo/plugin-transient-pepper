#!/bin/bash
# =============================================================================
# VST/AU Plugin PKG Build & Sign Script
# =============================================================================

# -----------------------
# 사용자 설정
# -----------------------
TEAM_ID="U4BB4TLGPQ"
PLUGIN_NAME="JE Transient Pepper"
PLUGIN_VERSION="1.0.3"
BUNDLE_ID="com.JoEunsoo.JETransientPepper"
DIST_XML="./pkg/Distribution.xml"
RESOURCES_PATH="./pkg/Resources"


# Developer ID 인증서
DEV_ID_APP="Developer ID Application: Eun Soo Jo ()"
DEV_ID_INSTALLER="Developer ID Installer: Eun Soo Jo ()"

# Apple Notarization
APPLE_ID="abc@abc.com"
APP_SPECIFIC_PASSWORD="0000-0000-0000-0000"

# 경로
BUILD_PATH="./Builds/MacOSX/build/Release"
AU_NAME="JE Transient Pepper.component"
VST3_NAME="JE Transient Pepper.vst3"

AU_PATH="$BUILD_PATH/$AU_NAME"
VST3_PATH="$BUILD_PATH/$VST3_NAME"

PKG_NAME="JETransientPepper-v${PLUGIN_VERSION}"
PKG_ROOT="./Builds/pkgroot"
PKG_OUTPUT_ROOT="./Builds"
PKG_OUTPUT="./Builds/${PKG_NAME}.pkg"
SIGNED_PKG_OUTPUT="./Builds/${PKG_NAME}-macOS-signed.pkg"

VST3_PKG_OUTPUT="${PKG_OUTPUT_ROOT}/${BUNDLE_ID}.vst3.pkg"
VST3_SIGNED_PKG_OUTPUT="${PKG_OUTPUT_ROOT}/${BUNDLE_ID}.vst3-signed.pkg"

AU_POST_POSTINSTALL_PATH="pkg/scripts/AU/postinstall"
VST3_POST_POSTINSTALL_PATH="pkg/scripts/VST3/postinstall"

# -----------------------
# 1. 패키지 루트 생성
# -----------------------
echo ">>> Creating package root..."
rm -rf "$PKG_ROOT"
mkdir -p "$PKG_ROOT/VST3/Library/Audio/Plug-Ins/VST3"
mkdir -p "$PKG_ROOT/AU/Library/Audio/Plug-Ins/Components"
mkdir -p "$PKG_ROOT/scripts/VST3"
mkdir -p "$PKG_ROOT/scripts/AU"

cp -R "$VST3_PATH" "$PKG_ROOT/VST3/Library/Audio/Plug-Ins/VST3/"
cp -R "$AU_PATH" "$PKG_ROOT/AU/Library/Audio/Plug-Ins/Components/"
cp -R "$VST3_POST_POSTINSTALL_PATH" "$PKG_ROOT/scripts/VST3/"
cp -R "$AU_POST_POSTINSTALL_PATH" "$PKG_ROOT/scripts/AU/"

chmod +x "$PKG_ROOT/scripts/VST3/postinstall"
chmod +x "$PKG_ROOT/scripts/AU/postinstall"

# -----------------------
# 2. 플러그인 서명
# -----------------------
echo ">>> Signing plugins..."
codesign --sign "$DEV_ID_APP" --deep --force "$PKG_ROOT/Library/Audio/Plug-Ins/VST3/$PLUGIN_NAME.vst3"
codesign --sign "$DEV_ID_APP" --deep --force "$PKG_ROOT/Library/Audio/Plug-Ins/Components/$PLUGIN_NAME.component"

# 서명 확인
codesign --verify --deep --strict "$PKG_ROOT/Library/Audio/Plug-Ins/VST3/$PLUGIN_NAME.vst3"
codesign --verify --deep --strict "$PKG_ROOT/Library/Audio/Plug-Ins/Components/$PLUGIN_NAME.component"

# -----------------------
# 3. PKG 생성 - VST3
# -----------------------
echo ">>> Building unsigned PKG..."
pkgbuild \
  --root "${PKG_ROOT}/VST3" \
  --identifier "${BUNDLE_ID}.vst3.pkg" \
  --version "$PLUGIN_VERSION" \
  --scripts "${PKG_ROOT}/scripts/VST3" \ 
  --install-location / \
  "${PKG_OUTPUT_ROOT}/${BUNDLE_ID}.vst3.pkg"
  
echo ">>> Building unsigned PKG..."
pkgbuild \
  --root "${PKG_ROOT}/AU" \
  --identifier "${BUNDLE_ID}.au.pkg" \
  --version "$PLUGIN_VERSION" \
  --scripts "${PKG_ROOT}/scripts/AU" \ 
  --install-location / \
  "${PKG_OUTPUT_ROOT}/${BUNDLE_ID}.au.pkg"

# -----------------------------
# 3. Distribution.xml 생성
# -----------------------------
echo "Creating Distribution.xml..."
cat > "$DIST_XML" <<EOL
<?xml version="1.0" encoding="utf-8"?>
<installer-gui-script minSpecVersion="1">
    <title>${PLUGIN_NAME}</title>
    <allowed-os-versions>
        <os-version min="10.13" />
    </allowed-os-versions>
    <license file="LICENSE.txt"/>
    <options customize="always" rootVolumeOnly="true" hostArchitectures="x86_64,arm64" />
    <domain enable_anywhere="false" enable_currentUserHome="false" enable_localSystem="true" />

    <choices-outline>
        <line choice="vst3" />
        <line choice="au" />
    </choices-outline>

    <choice id="vst3" visible="true" start_selected="true" title="${PLUGIN_NAME} VST3">
        <pkg-ref id="${BUNDLE_ID}.vst3.pkg" version="${PLUGIN_VERSION}">${BUNDLE_ID}.vst3.pkg</pkg-ref>
    </choice>

    <choice id="au" visible="true" start_selected="true" title="${PLUGIN_NAME} AU">
        <pkg-ref id="${BUNDLE_ID}.au.pkg" version="${PLUGIN_VERSION}">${BUNDLE_ID}.au.pkg</pkg-ref>
    </choice>

</installer-gui-script>
EOL

# -----------------------
# 4. PKG 서명
# -----------------------
echo ">>> Signing PKG..."
  
productbuild \
  --distribution "$DIST_XML" \
  --resources "$RESOURCES_PATH" \
  --package-path "./Builds" \
  --sign "$DEV_ID_INSTALLER" \
  "$SIGNED_PKG_OUTPUT"

# 서명 확인
spctl -a -t install "$SIGNED_PKG_OUTPUT"

# -----------------------
# 5. Notarization 제출 및 완료 확인 (notarytool)
# -----------------------
echo ">>> Submitting notarization request with notarytool..."
xcrun notarytool submit "$SIGNED_PKG_OUTPUT" \
  --apple-id "$APPLE_ID" \
  --team-id "$TEAM_ID" \
  --password "$APP_SPECIFIC_PASSWORD" \
  --wait \
  --output-format json

if [ $? -eq 0 ]; then
    echo ">>> Notarization completed successfully!"
    echo ">>> Stapling the PKG..."
    xcrun stapler staple "$SIGNED_PKG_OUTPUT"
    echo ">>> Stapling done. PKG is ready for distribution."
else
    echo ">>> Notarization failed. Check the output above for details."
fi

echo ">>> Final signed and notarized PKG: $SIGNED_PKG_OUTPUT"