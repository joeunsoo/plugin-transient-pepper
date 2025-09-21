import ToggleButton, { type BlurToggleButtonProps } from '@/ui/BlurToggleButton';
import { GlassSx, LabelTypographySx } from '@/define';
import { Text } from '@mantine/core';

export interface ToggleButtonProps
  extends BlurToggleButtonProps {
  label: string | number
}

export default function StyledToggleButton({
  label,
  onMouseDown,
  ...props
}: ToggleButtonProps) {

  return (
    <ToggleButton
      my="0.2em"
      py="0.5em"
      style={{
        width: '100%',
        border: '0.1em solid var(--mantine-color-primary-9)',
        borderRadius: '0.3em',
        background: 'linear-gradient(135deg, var(--mui-palette-secondary-darker), var(--mui-palette-secondary-blackest))',
      }}

      sx={{
        ...GlassSx,
        '&[data-value="true"]': {
          background: 'linear-gradient(135deg, var(--mui-palette-secondary-main), var(--mui-palette-secondary-dark)) !important',
        },
      }}

      onMouseDown={(e) => {
        onMouseDown?.(e);
        e.preventDefault();
      }}

      {...props}
    >
      <Text
        sx={{
          ...LabelTypographySx,
        }}
      >
        {label}
      </Text>
    </ToggleButton>
  );
}
