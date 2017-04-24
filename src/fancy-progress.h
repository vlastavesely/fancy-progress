#ifndef __FANCY_PROGRESS_H
#define __FANCY_PROGRESS_H

/**
 * Prepares tty screen for progress bar.
 */
void fancy_progress_start(void);

/**
 * Renders progress bar.
 * @progress: a progress value (0 - 100)
 */
void fancy_progress_step(float progress);

/**
 * Removes progress bar and restores original tty screen size.
 */
void fancy_progress_stop(void);

#endif /* __FANCY_PROGRESS_H */
