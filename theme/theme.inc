<?php

/**
 * @file
 * Theme hooks.
 */

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_subset(&$variables) {
  $islandora_object = menu_get_object('islandora_object', 2);
  module_load_include('inc', 'islandora', 'includes/metadata');
  if ($islandora_object) {
    $page_number = (empty($_GET['page'])) ? 0 : $_GET['page'];
    $page_size = (empty($_GET['pagesize'])) ? variable_get('islandora_basic_collection_page_size', '10') : $_GET['pagesize'];

    if (isset($islandora_object['TN_LARGE'])) {
      $collection_tn_url = url("islandora/object/{$islandora_object->id}/datastream/TN_LARGE/view");
      $params = array(
        'title' => $islandora_object->label,
        'alt' => $islandora_object->label,
        'path' => $collection_tn_url);
      $variables['collection_img'] = theme('image', $params);
    }
    $variables['collection_metadata'] = islandora_retrieve_metadata_markup($islandora_object);
  }
  $variables['display_links'] = array();
  $variables['pager'] = '';
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_grid(&$variables) {
  $islandora_object = menu_get_object('islandora_object', 2);
  $variables['view_links'] = array();
  _get_solr_results($islandora_object, $variables);
}

/**
 * Helper function to get the solr search results HTML for the various
 * templates that need it.  This will set the $variables['solr_search'] value.
 *
 * @param type $islandora_object
 * @param array $variables
 */
function _get_solr_results($islandora_object, &$variables) {
  if (isset($variables['solr_search']) && $variables['solr_search'] <> '') { return; }
  // Inspect the islandora_object to get the PID match for the SOLR query.
  $solr_query = 'RELS_EXT_isMemberOfCollection_uri_ms:"info:fedora/' . $islandora_object->id . '"';
  $variables['solr_search'] = islandora_solr($solr_query);
}

function _get_solr_sidebar_blocks() {
  $sort_block = module_invoke('islandora_solr', 'block_view', 'sort');
  $facets_block = module_invoke('islandora_solr', 'block_view', 'basic_facets');
  return '
<div id="sidebar">
 <!-- div class="widget" -->
  <!-- div class="region region-sidebar" -->
        <div class="region region-sidebar">' .
_my_theme_solr_block($sort_block, 'upitt_islandora_solr_search_extras', 'sort') .
    _my_theme_solr_block($facets_block, 'upitt_islandora_solr_search_extras', 'basic_facets') . '
        </div>
  <!-- /div -->
 <!-- /div -->
</div>
';
}

function _my_theme_solr_block($block, $block_module, $block_delta) {
  return '
<div id="' . drupal_html_id('block-islandora-solr-' . $block_delta) . '" class="block block-islandora-solr">
' . (isset($block['subject']) ? '
  <h2>' . $block['subject'] . '</h2>' : '') .
'  <div class="content">
    ' . $block['content'] .
'  </div>
</div> 
';
}

