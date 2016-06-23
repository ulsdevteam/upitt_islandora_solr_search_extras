<?php

/**
 * @file
 * Theme hooks.
 */

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_wrapper(&$variables, $hook) {
  $islandora_object = $variables['islandora_object'];
  $form = drupal_get_form('search_in_collection', $islandora_object->id, $islandora_object->label);
  $variables['collection_search'] = drupal_render($form);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection(&$variables, $hook) {
  $islandora_object = $variables['islandora_object'];
  $form = drupal_get_form('search_in_collection', $islandora_object->id, $islandora_object->label);
  $variables['collection_search'] = drupal_render($form);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_list(&$variables, $hook) {
  $islandora_object = $variables['islandora_object'];
  $form = drupal_get_form('search_in_collection', $islandora_object->id, $islandora_object->label);
  $variables['collection_search'] = drupal_render($form);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_grid(&$variables, $hook) {
  $islandora_object = $variables['islandora_object'];
  $form = drupal_get_form('search_in_collection', $islandora_object->id, $islandora_object->label);
  $variables['collection_search'] = drupal_render($form);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_list(&$variables) {
  $islandora_object = menu_get_object('islandora_object', 2);

  if (!is_object($islandora_object)) {
    // Take first object and use relationships to get the parent object.
    $child_object = $variables['objects'][0];
    $link = $child_object['link'];
  }
  $form = drupal_get_form('search_in_collection', $islandora_object->id, $islandora_object->label);
  $variables['collection_search'] = drupal_render($form);
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_grid(&$variables) {
  $islandora_object = menu_get_object('islandora_object', 2);

  if (!is_object($islandora_object)) {
    // Take first object and use relationships to get the parent object.
    $child_object = $variables['objects'][0];
    $link = $child_object['link'];
  }
  $form = drupal_get_form('search_in_collection', $islandora_object->id, $islandora_object->label);
  $variables['collection_search'] = drupal_render($form);
}

