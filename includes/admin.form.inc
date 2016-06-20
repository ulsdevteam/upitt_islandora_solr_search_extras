<?php

/**
 * @file
 * Handles the display/submission of the admin settings form for this module.
 */

/**
 * Defines the admin settings form.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 */
function upitt_islandora_solr_search_extras_admin_settings(array $form, array &$form_state) {
  $form = array(
    'showparent_searchresults' => array(
      '#type' => 'checkbox',
      '#title' => t('Show parent info for any collection items in search results.'),
      '#description' => t('When enabled, will show the parent item information for any collection items in search results.'),
      '#default_value' => variable_get('upitt_islandora_solr_search_extras_showparent_searchresults', 0),
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
    ),
    'reset' => array(
      '#type' => 'submit',
      '#value' => t('Reset to defaults'),
    ),
  );

  return $form;
}

/**
 * Function that sets the Drupal variables with user's input.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 */
function upitt_islandora_solr_search_extras_admin_settings_submit(array $form, array &$form_state) {
  drupal_set_message(t('The settings have been updated!'));
  $id = $form_state['triggering_element']['#id'];
  switch ($id) {
    case 'edit-submit':
      variable_set('upitt_islandora_solr_search_extras_showparent_searchresults', $form_state['values']['showparent_searchresults']);
      break;

    case 'edit-reset':
      variable_del('upitt_islandora_solr_search_extras_showparent_searchresults');
      break;
  }
}

