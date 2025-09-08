'use client';

import { useState, useEffect } from 'react';
import * as Juce from 'juce-framework-frontend';

import Box from '@mui/material/Box';
import InputLabel from '@mui/material/InputLabel';
import MenuItem from '@mui/material/MenuItem';
import FormControl from '@mui/material/FormControl';
import Select, { type SelectChangeEvent } from '@mui/material/Select';

import controlParameterIndexAnnotation from '@/src/define/controlParameterIndexAnnotation';

type JuceComboBoxProps = {
  identifier: string,
}

export default function JuceComboBox({
  identifier
}: JuceComboBoxProps) {
  const comboBoxState = Juce.getComboBoxState(identifier);

  const [value, setValue] = useState(comboBoxState.getChoiceIndex());
  const [properties, setProperties] = useState(comboBoxState.properties);

  const handleChange = (event: SelectChangeEvent) => {
    comboBoxState.setChoiceIndex(event.target.value);
    setValue(event.target.value);
  };

  useEffect(() => {
    const valueListenerId = comboBoxState.valueChangedEvent.addListener(() => {
      setValue(comboBoxState.getChoiceIndex());
    });
    const propertiesListenerId =
      comboBoxState.propertiesChangedEvent.addListener(() => {
        setProperties(comboBoxState.properties);
      });

    return function cleanup() {
      comboBoxState.valueChangedEvent.removeListener(valueListenerId);
      comboBoxState.propertiesChangedEvent.removeListener(propertiesListenerId);
    };
  });

  return (
    <Box
      {...{
        [controlParameterIndexAnnotation]:
          comboBoxState.properties.parameterIndex,
      }}
    >
      <FormControl fullWidth>
        <InputLabel id={identifier}>{properties.name}</InputLabel>
        <Select
          labelId={identifier}
          value={value}
          label={properties.name}
          onChange={handleChange}
        >
          {properties.choices.map((choice: number|string, i: number) => (
            <MenuItem value={i} key={i}>
              {choice}
            </MenuItem>
          ))}
        </Select>
      </FormControl>
    </Box>
  );
}
