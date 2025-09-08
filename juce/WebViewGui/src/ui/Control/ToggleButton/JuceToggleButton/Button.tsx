'use client';

import StyledToggleButton from '@/src/ui/StyledToggleButton';

type JuceCheckboxProps = {
  value: boolean,
  handleChange: (value: boolean) => void
  label: string
}

export default function JuceCheckbox({
  value,
  handleChange,
  label
}: JuceCheckboxProps) {

  const handleMouseDown = () => {
    handleChange(!value);
  };

  return (
    <StyledToggleButton
      value={value}
      label={label}
      onMouseDown={handleMouseDown}
      className={value ? 'Mui-selected' : ''}
    />
  );
}
