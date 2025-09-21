import { Text } from '@mantine/core';
import { GlassSx, LabelTypographySx } from '@/define';
import ToggleButton, { type BlurToggleButtonProps } from '@/ui/BlurToggleButton';

export interface ToggleButtonProps extends BlurToggleButtonProps {
  label: string | number;
}

export default function StyledToggleButton({ label, onMouseDown, ...props }: ToggleButtonProps) {
  return (
    <ToggleButton
      my="0.2em"
      py="0.5em"
      px={0}
      style={{
        width: '100%',
        border: '0.1em solid var(--mantine-color-primary-9)',
        borderRadius: '0.3em',
        background:
          'linear-gradient(135deg, var(--mantine-color-secondaryDark-6), var(--mantine-color-secondaryDark-9))',
      }}
      sx={{
        ...GlassSx,
        '&[data-value="true"]': {
          background:
            'linear-gradient(135deg, var(--mantine-color-secondaryDark-0), var(--mantine-color-secondaryDark-2)) !important',
        },
      }}
      onMouseDown={(e) => {
        onMouseDown?.(e);
        e.preventDefault();
      }}
      {...props}
    >
      <Text
        component="span"
        fw={500}
        sx={{
          ...LabelTypographySx,
        }}
      >
        {label}
      </Text>
    </ToggleButton>
  );
}
