'use client';

import { notifications } from '@mantine/notifications';
import { useEffect } from 'react';

import { useSnackbarStore } from '@/store/SnackbarStore';

import classes from './Snackbar.module.css';
import { InfoIcon, WarningIcon } from '@phosphor-icons/react';

export default function Demo() {
  const { refreshCount, open, onClose, message, options } = useSnackbarStore();

  useEffect(() => {
    if (open) {
      let color = 'primary.4';
      let icon = <InfoIcon size="1.0rem" color="white" />;
      if (options.variant === 'success') {
        color = 'green';
      } else if (options.variant === 'error') {
        color = 'red';
        icon = <WarningIcon
          size="1.0rem"
          weight="bold"
        />;
      }

      notifications.show({
        message,
        position: 'bottom-left',
        color,
        icon,
        autoClose: 3000,
        onClose,
        classNames: classes,
        w:'fit-content',
        styles: {
          root: {
            padding:'0.2em',
            paddingLeft:'0.5em',
            paddingRight:'0.5em',
          },
          icon: {
            margin: 0
          }
        }
      });
    }
  }, [refreshCount, open, message, options, onClose]);
  return null;
}
