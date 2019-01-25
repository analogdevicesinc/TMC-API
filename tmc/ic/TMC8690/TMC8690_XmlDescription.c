
// ===== used for xml file generation =====

// \xml <?xml version="1.0" encoding="UTF-8" standalone="no"?>
// \xml <tmc:product_ic name="TMC8690" version="1.0" author="OM, BS" xmlns:tmc="http://www.trinamic.com" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="https://www.trinamic.com https://www.trinamic.com/fileadmin/xml/TMC_Schema.xsd">
// \xml <tmc:register_set for="TMC8690" name="All Registers">

// \xml <tmc:group name="Status information"       id="#GROUP_STATUS_INFORMATION#"></tmc:group>
// \xml <tmc:group name="General settings"         id="#GROUP_GENERAL_SETTINGS#"></tmc:group>
// \xml <tmc:group name="ADCs"                     id="#GROUP_ADCS#"></tmc:group>
// \xml <tmc:group name="Inputs/Outputs"           id="#GROUP_IO#"></tmc:group>
// \xml <tmc:group name="PWM"                      id="#GROUP_PWM#"></tmc:group>
// \xml <tmc:group name="Decoder ABN"              id="#GROUP_DECODER_ABN#"></tmc:group>
// \xml <tmc:group name="Hall digital"             id="#GROUP_HALL_DIGITAL#"></tmc:group>
// \xml <tmc:group name="Hall analog"              id="#GROUP_HALL_ANALOG#"></tmc:group>
// \xml <tmc:group name="Decoder analog"           id="#GROUP_DECODER_ANALOG#"></tmc:group>
// \xml <tmc:group name="PID regulators"           id="#GROUP_PID_REGULATORS#"></tmc:group>


// \xml <tmc:value_register address="#CHIPINFO_DATA#" name="CHIPINFO_DATA" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="Variant 0">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="SI_TYPE" shift="0" mask="FFFFFFFF" desc="">
// \xml          <tmc:value_ascii desc="Hardware type (ASCII)." access="R"></tmc:value_ascii>
// \xml       </tmc:value_register_field>
// \xml       <tmc:register_variant_impacted_by address="#CHIPINFO_ADDR#" shift="0" mask="FFFFFFFF" range_from="0" range_to="0"></tmc:register_variant_impacted_by>
// \xml    </tmc:register_variant>

// \xml    <tmc:register_variant name="Variant 1">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="SI_VERSION" shift="0" mask="FFFFFFFF" desc="">
// \xml          <tmc:value_version desc="Hardware version (u16.u16)." access="R"></tmc:value_version>
// \xml       </tmc:value_register_field>
// \xml       <tmc:register_variant_impacted_by address="#CHIPINFO_ADDR#" shift="0" mask="FFFFFFFF" range_from="1" range_to="1"></tmc:register_variant_impacted_by>
// \xml    </tmc:register_variant>

// \xml    <tmc:register_variant name="Variant 2">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="SI_DATE" shift="0" mask="FFFFFFFF" desc="">
// \xml          <tmc:value_date desc="Hardware date (nibble wise date stamp yyyymmdd)." access="R"></tmc:value_date>
// \xml       </tmc:value_register_field>
// \xml       <tmc:register_variant_impacted_by address="#CHIPINFO_ADDR#" shift="0" mask="FFFFFFFF" range_from="2" range_to="2"></tmc:register_variant_impacted_by>
// \xml    </tmc:register_variant>

// \xml    <tmc:register_variant name="Variant 3">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="SI_TIME" shift="0" mask="FFFFFFFF" desc="">
// \xml          <tmc:value_time desc="Hardware time (nibble wise time stamp --hhmmss)" access="R"></tmc:value_time>
// \xml       </tmc:value_register_field>
// \xml       <tmc:register_variant_impacted_by address="#CHIPINFO_ADDR#" shift="0" mask="FFFFFFFF" range_from="3" range_to="3"></tmc:register_variant_impacted_by>
// \xml    </tmc:register_variant>

// \xml </tmc:value_register>

// \xml <tmc:value_register address="#CHIPINFO_ADDR#" name="CHIPINFO_ADDR" size="32"  group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc>Chip info address</desc>
// \xml       <tmc:value_register_field name="CHIP_INFO_ADDRESS" shift="0" mask="000000FF" desc="">
// \xml          <tmc:value_choice default="0" unit="" access="RW">
// \xml            <choice_element value="0" desc="SI_TYPE"></choice_element>
// \xml            <choice_element value="1" desc="SI_VERSION"></choice_element>
// \xml            <choice_element value="2" desc="SI_DATE"></choice_element>
// \xml            <choice_element value="3" desc="SI_TIME"></choice_element>
// \xml          </tmc:value_choice>
// \xml       </tmc:value_register_field>
// \xml       <tmc:register_variant_impacts address="#CHIPINFO_DATA#"></tmc:register_variant_impacts>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>

// \xml <tmc:value_register address="#STATUS_WORD#" name="STATUS_WORD" size="32" group="#GROUP_EMPTY#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="STATUS_WORD" shift="0" mask="FFFFFFFF" desc="description of STATUS_WORD">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>

// \xml <tmc:value_register address="#COMMAND_WORD#" name="COMMAND_WORD" size="32" group="#GROUP_EMPTY#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="COMMAND_WORD" shift="0" mask="FFFFFFFF" desc="description of COMMAND_WORD">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#P_FAK_BRAKE#" name="P_FAK_BRAKE" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="P_FAK_BRAKE" shift="0" mask="0000FFFF" desc="description of P_FAK_BRAKE">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="RW"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#I_FAK_BRAKE#" name="I_FAK_BRAKE" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="I_FAK_BRAKE" shift="0" mask="0000FFFF" desc="description of I_FAK_BRAKE">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="RW"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#P_FAK_HEAT#" name="P_FAK_HEAT" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="P_FAK_HEAT" shift="0" mask="0000FFFF" desc="description of P_FAK_HEAT">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="RW"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#I_FAK_HEAT#" name="I_FAK_HEAT" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="I_FAK_HEAT" shift="0" mask="0000FFFF" desc="description of I_FAK_HEAT">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="RW"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#P_FAK_VEL#" name="P_FAK_VEL" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="P_FAK_VEL" shift="0" mask="0000FFFF" desc="description of P_FAK_VEL">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="RW"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#I_FAK_VEL#" name="I_FAK_VEL" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="I_FAK_VEL" shift="0" mask="0000FFFF" desc="description of I_FAK_VEL">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="RW"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#P_FAK_POS#" name="P_FAK_POS" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="P_FAK_POS" shift="0" mask="0000FFFF" desc="description of P_FAK_POS">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="RW"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ENC_Z_COMP_VAL#" name="ENC_Z_COMP_VAL" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ENC_Z_COMP_VAL" shift="0" mask="0000FFFF" desc="description of ENC_Z_COMP_VAL">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="RW"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#TORQUE_TARGET#" name="TORQUE_TARGET" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="TORQUE_TARGET" shift="0" mask="0000FFFF" desc="description of TORQUE_TARGET">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="RW"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#VELOCITY_TARGET#" name="VELOCITY_TARGET" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="VELOCITY_TARGET" shift="0" mask="FFFFFFFF" desc="description of VELOCITY_TARGET">
// \xml          <tmc:value_signed min="#s32_MIN#" max="#s32_MAX#" default="0" unit="" access="RW"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#POSITION_TARGET#" name="POSITION_TARGET" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="POSITION_TARGET" shift="0" mask="FFFFFFFF" desc="description of POSITION_TARGET">
// \xml          <tmc:value_signed min="#s32_MIN#" max="#s32_MAX#" default="0" unit="" access="RW"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#TEMPERATURE_TARGET#" name="TEMPERATURE_TARGET" size="32" group="#GROUP_STATUS_INFORMATION#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="TEMPERATURE_TARGET" shift="0" mask="0000FFFF" desc="description of TEMPERATURE_TARGET">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#OSCI_MAIN_CONFIG_REG#" name="OSCI_MAIN_CONFIG_REG" size="32" group="#GROUP_GENERAL_SETTINGS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="OSCI_MAIN_CONFIG_REG" shift="0" mask="FFFFFFFF" desc="description of OSCI_MAIN_CONFIG_REG">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#OSCI_PRETRIGGER_CONFIG_REG#" name="OSCI_PRETRIGGER_CONFIG_REG" size="32" group="#GROUP_GENERAL_SETTINGS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="OSCI_PRETRIGGER_CONFIG_REG" shift="0" mask="0000FFFF" desc="description of OSCI_PRETRIGGER_CONFIG_REG">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#OSCI_DATA_ADDRESS#" name="OSCI_DATA_ADDRESS" size="32" group="#GROUP_GENERAL_SETTINGS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="OSCI_DATA_ADDRESS" shift="0" mask="0000FFFF" desc="description of OSCI_DATA_ADDRESS">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#OSCI_STATUS#" name="OSCI_STATUS" size="32" group="#GROUP_GENERAL_SETTINGS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="OSCI_STATUS" shift="0" mask="0000FFFF" desc="description of OSCI_STATUS">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="R"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#OSCI_OUTPUT_DATA#" name="OSCI_OUTPUT_DATA" size="32" group="#GROUP_GENERAL_SETTINGS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="OSCI_OUTPUT_DATA" shift="0" mask="0000FFFF" desc="description of OSCI_OUTPUT_DATA">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="R"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ADC_ENC_TRACK_A#" name="ADC_ENC_TRACK_A" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ADC_ENC_TRACK_A" shift="0" mask="0000FFFF" desc="description of ADC_ENC_TRACK_A">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="R"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ADC_ENC_TRACK_B#" name="ADC_ENC_TRACK_B" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ADC_ENC_TRACK_B" shift="0" mask="0000FFFF" desc="description of ADC_ENC_TRACK_B">
// \xml          <tmc:value_signed min="#s16_MIN#" max="#s16_MAX#" default="0" unit="" access="R"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ADC_ENC_TRACK_Z#" name="ADC_ENC_TRACK_Z" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ADC_ENC_TRACK_Z" shift="0" mask="0000FFFF" desc="description of ADC_ENC_TRACK_Z">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ADC_I_U#" name="ADC_I_U" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ADC_I_U" shift="0" mask="0000FFFF" desc="description of ADC_I_U">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ADC_I_V#" name="ADC_I_V" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ADC_I_V" shift="0" mask="0000FFFF" desc="description of ADC_I_V">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ADC_I_W#" name="ADC_I_W" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ADC_I_W" shift="0" mask="0000FFFF" desc="description of ADC_I_W">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ADC_I_SUPPLY#" name="ADC_I_SUPPLY" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ADC_I_SUPPLY" shift="0" mask="FFFFFFFF" desc="description of ADC_I_SUPPLY">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ADC_I_SUPPLY_FILT#" name="ADC_I_SUPPLY_FILT" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ADC_I_SUPPLY_FILT" shift="0" mask="FFFFFFFF" desc="description of ADC_I_SUPPLY_FILT">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ADC_TORQUE#" name="ADC_TORQUE" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ADC_TORQUE" shift="0" mask="0000FFFF" desc="description of ADC_TORQUE">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ADC_TEMP#" name="ADC_TEMP" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ADC_TEMP" shift="0" mask="0000FFFF" desc="description of ADC_TEMP">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ADC_MICROPHONE#" name="ADC_MICROPHONE" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ADC_MICROPHONE" shift="0" mask="0000FFFF" desc="description of ADC_MICROPHONE">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ADC_I_BRAKE#" name="ADC_I_BRAKE" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ADC_I_BRAKE" shift="0" mask="0000FFFF" desc="description of ADC_I_BRAKE">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#TRACK_A_OFFSET#" name="TRACK_A_OFFSET" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="TRACK_A_OFFSET" shift="0" mask="0000FFFF" desc="description of TRACK_A_OFFSET">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#TRACK_B_OFFSET#" name="TRACK_B_OFFSET" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="TRACK_B_OFFSET" shift="0" mask="0000FFFF" desc="description of TRACK_B_OFFSET">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#DAC_V_REF#" name="DAC_V_REF" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="DAC_V_REF" shift="0" mask="0000FFFF" desc="description of DAC_V_REF">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#T_PT1_FILTER_VEL#" name="T_PT1_FILTER_VEL" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="T_PT1_FILTER_VEL" shift="0" mask="0000FFFF" desc="description of T_PT1_FILTER_VEL">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#T_PT1_FILTER_I_SUPPLY#" name="T_PT1_FILTER_I_SUPPLY" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="T_PT1_FILTER_I_SUPPLY" shift="0" mask="0000FFFF" desc="description of T_PT1_FILTER_I_SUPPLY">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#DAC_BRAKE#" name="DAC_BRAKE" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="DAC_BRAKE" shift="0" mask="FFFFFFFF" desc="description of DAC_BRAKE">
// \xml          <tmc:value_signed min="#s32_MIN#" max="#s32_MAX#" default="0" unit="" access="R"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#DAC_BRAKE_TARGET#" name="DAC_BRAKE_TARGET" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="DAC_BRAKE_TARGET" shift="0" mask="FFFFFFFF" desc="description of DAC_BRAKE_TARGET">
// \xml          <tmc:value_signed min="#s32_MIN#" max="#s32_MAX#" default="0" unit="" access="RW"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#VELOCITY_ACTUAL#" name="VELOCITY_ACTUAL" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="VELOCITY_ACTUAL" shift="0" mask="FFFFFFFF" desc="description of VELOCITY_ACTUAL">
// \xml          <tmc:value_signed min="#s32_MIN#" max="#s32_MAX#" default="0" unit="" access="R"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#VELOCITY_IN_RPM_ACTUAL#" name="VELOCITY_IN_RPM_ACTUAL" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="VELOCITY_IN_RPM_ACTUAL" shift="0" mask="FFFFFFFF" desc="description of VELOCITY_IN_RPM_ACTUAL">
// \xml          <tmc:value_signed min="#s32_MIN#" max="#s32_MAX#" default="0" unit="" access="R"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#VELOCITY_IN_RPM_ACTUAL_PT1#" name="VELOCITY_IN_RPM_ACTUAL_PT1" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="VELOCITY_IN_RPM_ACTUAL_PT1" shift="0" mask="FFFFFFFF" desc="description of VELOCITY_IN_RPM_ACTUAL_PT1">
// \xml          <tmc:value_signed min="#s32_MIN#" max="#s32_MAX#" default="0" unit="" access="R"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#VELOCITY_IN_RPM_ACTUAL_MAV#" name="VELOCITY_IN_RPM_ACTUAL_MAV" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="VELOCITY_IN_RPM_ACTUAL_MAV" shift="0" mask="FFFFFFFF" desc="description of VELOCITY_IN_RPM_ACTUAL_MAV">
// \xml          <tmc:value_signed min="#s32_MIN#" max="#s32_MAX#" default="0" unit="" access="R"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#POSITION_ACTUAL#" name="POSITION_ACTUAL" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="POSITION_ACTUAL" shift="0" mask="FFFFFFFF" desc="description of POSITION_ACTUAL">
// \xml          <tmc:value_signed min="#s32_MIN#" max="#s32_MAX#" default="0" unit="" access="R"></tmc:value_signed>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#VEL_CTRL_TORQUE_TARGET#" name="VEL_CTRL_TORQUE_TARGET" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="VEL_CTRL_TORQUE_TARGET" shift="0" mask="0000FFFF" desc="description of VEL_CTRL_TORQUE_TARGET">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#POS_CTRL_VEL_TARGET#" name="POS_CTRL_VEL_TARGET" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="POS_CTRL_VEL_TARGET" shift="0" mask="0000FFFF" desc="description of POS_CTRL_VEL_TARGET">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#PWM_HEATER#" name="PWM_HEATER" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="PWM_HEATER" shift="0" mask="0000FFFF" desc="description of PWM_HEATER">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#U_BRAKE#" name="U_BRAKE" size="32" group="#GROUP_IO#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="U_BRAKE" shift="0" mask="0000FFFF" desc="description of U_BRAKE">
// \xml          <tmc:value_unsigned min="0" max="#u16_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#DEBUG_AXIS_PARAM_0#" name="DEBUG_AXIS_PARAM_0" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="DEBUG_AXIS_PARAM_0" shift="0" mask="FFFFFFFF" desc="description of DEBUG_AXIS_PARAM_0">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#DEBUG_AXIS_PARAM_1#" name="DEBUG_AXIS_PARAM_1" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="DEBUG_AXIS_PARAM_1" shift="0" mask="FFFFFFFF" desc="description of DEBUG_AXIS_PARAM_1">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#DEBUG_AXIS_PARAM_2#" name="DEBUG_AXIS_PARAM_2" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="DEBUG_AXIS_PARAM_2" shift="0" mask="FFFFFFFF" desc="description of DEBUG_AXIS_PARAM_2">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#DEBUG_AXIS_PARAM_3#" name="DEBUG_AXIS_PARAM_3" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="DEBUG_AXIS_PARAM_3" shift="0" mask="FFFFFFFF" desc="description of DEBUG_AXIS_PARAM_3">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#DEBUG_AXIS_PARAM_4#" name="DEBUG_AXIS_PARAM_4" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="DEBUG_AXIS_PARAM_4" shift="0" mask="FFFFFFFF" desc="description of DEBUG_AXIS_PARAM_4">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#DEBUG_AXIS_PARAM_5#" name="DEBUG_AXIS_PARAM_5" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="DEBUG_AXIS_PARAM_5" shift="0" mask="FFFFFFFF" desc="description of DEBUG_AXIS_PARAM_5">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#DEBUG_AXIS_PARAM_6#" name="DEBUG_AXIS_PARAM_6" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="DEBUG_AXIS_PARAM_6" shift="0" mask="FFFFFFFF" desc="description of DEBUG_AXIS_PARAM_6">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#DEBUG_AXIS_PARAM_7#" name="DEBUG_AXIS_PARAM_7" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="DEBUG_AXIS_PARAM_7" shift="0" mask="FFFFFFFF" desc="description of DEBUG_AXIS_PARAM_7">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#STATE_VAR_PARAM_0#" name="STATE_VAR_PARAM_0" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="STATE_VAR_PARAM_0" shift="0" mask="FFFFFFFF" desc="description of STATE_VAR_PARAM_0">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#STATE_VAR_PARAM_1#" name="STATE_VAR_PARAM_1" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="STATE_VAR_PARAM_1" shift="0" mask="FFFFFFFF" desc="description of STATE_VAR_PARAM_1">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#STATE_VAR_PARAM_2#" name="STATE_VAR_PARAM_2" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="STATE_VAR_PARAM_2" shift="0" mask="FFFFFFFF" desc="description of STATE_VAR_PARAM_2">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#STATE_VAR_PARAM_3#" name="STATE_VAR_PARAM_3" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="STATE_VAR_PARAM_3" shift="0" mask="FFFFFFFF" desc="description of STATE_VAR_PARAM_3">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#STATE_VAR_PARAM_4#" name="STATE_VAR_PARAM_4" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="STATE_VAR_PARAM_4" shift="0" mask="FFFFFFFF" desc="description of STATE_VAR_PARAM_4">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#STATE_VAR_PARAM_5#" name="STATE_VAR_PARAM_5" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="STATE_VAR_PARAM_5" shift="0" mask="FFFFFFFF" desc="description of STATE_VAR_PARAM_5">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#STATE_VAR_PARAM_6#" name="STATE_VAR_PARAM_6" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="STATE_VAR_PARAM_6" shift="0" mask="FFFFFFFF" desc="description of STATE_VAR_PARAM_6">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#STATE_VAR_PARAM_7#" name="STATE_VAR_PARAM_7" size="32" group="#GROUP_ADCS#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="STATE_VAR_PARAM_7" shift="0" mask="FFFFFFFF" desc="description of STATE_VAR_PARAM_7">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#SAMP_INPUTS_RAW#" name="SAMP_INPUTS_RAW" size="32" group="#GROUP_PWM#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="SAMP_INPUTS_RAW" shift="0" mask="FFFFFFFF" desc="description of SAMP_INPUTS_RAW">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#SAMP_OUTPUTS_RAW#" name="SAMP_OUTPUTS_RAW" size="32" group="#GROUP_PWM#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="SAMP_OUTPUTS_RAW" shift="0" mask="FFFFFFFF" desc="description of SAMP_OUTPUTS_RAW">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="R"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#STATUS_FLAGS#" name="STATUS_FLAGS" size="32" group="#GROUP_PWM#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="STATUS_FLAGS" shift="0" mask="FFFFFFFF" desc="description of STATUS_FLAGS">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#WARNING_MASK#" name="WARNING_MASK" size="32" group="#GROUP_PWM#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="WARNING_MASK" shift="0" mask="FFFFFFFF" desc="description of WARNING_MASK">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml <tmc:value_register address="#ERROR_MASK#" name="ERROR_MASK" size="32" group="#GROUP_PWM#">
// \xml    <tmc:register_variant name="DEFAULT">
// \xml       <desc></desc>
// \xml       <tmc:value_register_field name="ERROR_MASK" shift="0" mask="FFFFFFFF" desc="description of ERROR_MASK">
// \xml          <tmc:value_unsigned min="0" max="#u32_MAX#" default="0" unit="" access="RW"></tmc:value_unsigned>
// \xml       </tmc:value_register_field>
// \xml    </tmc:register_variant>
// \xml </tmc:value_register>


// \xml </tmc:register_set>
// \xml </tmc:product_ic>
